#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <dirent.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define CONSUMER_COUNT 2
#define PRODUCER_COUNT 2
#define DATABASE_DIR "database"
#define DATABASE_SIZE 100
int dirlen = strlen(DATABASE_DIR)+10;

sem_t semBufferEmpty;
sem_t semBufferFull;
pthread_mutex_t mutexBuffer;
pthread_mutex_t mutexMcount;
pthread_mutex_t mutexQueue;

typedef struct Task{
	char filename[40];
}Task;

typedef struct entry {
	char name[50];
	char address[80];
	char phone[10];
	char d[3];
	char m[3];
	char y[5];
	char occupation[60];
	int salary;
	char filename[50];
}entry;

Task Queue[DATABASE_SIZE];			// Filename queue of files in directory
int queueCount = 0;

entry entries[BUFFER_SIZE];			// Mutual buffer for Prod/Cons threads
int bufferCount = 0;

int salaryAvg = 0;
int mcount[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
entry winner;
int winnerFlag = 0;					// Indicates to all threads to terminate in case of a match with arguments
int emptyBufferFlag = 0;			// Indicates to Consumers that Producers will terminate and won't update buffer
int file_count = 0;
int filesFlag = 0;
int Producer_count = 0;				// Counts how many times Producers executed their function
int Consumer_count = 0;				// Counts how many times Consumers executed their function (will be used for average)

void prt_entry(entry person){
	/*
	Print Persons entry according to following format:
	Name: <John Johnson>
	Address: <Street 123, City, Country>
	Phone: <123456789>
	Date of birth: <YYYY-MM-DD>
	Occupation: <company, position>
	Salary: <$$$$$$$>
	*/
	printf("Name: <%s>\n",person.name);
	printf("Address: <%s>\n",person.address);
	printf("Phone: <%s>\n",person.phone);
	printf("Date of birth: <%s-%s-%s>\n",person.y,person.m,person.d);
	printf("Occupation: <%s>\n",person.occupation);
	printf("Salary: <%d>\n",person.salary);
}
void prt_histogram(int *countts){
	/*
	Prints a correctly formated Months birthdates count.
	Takes an array of counts per month. Will construct a correctly formatted separators and
	print correctly formatted information like this:
	+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	| Jan | Feb | Mar | Apr | May | Jun | Jul | Aug | Sep | Oct | Nov | Dec |
	+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	|   4 |   8 |   7 |   7 |   8 |   2 |   9 |   7 |   6 |   4 |  10 |   9 |
	+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	*/
	int fcnt = 0;
	char* months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	int spaces[12];
	char formatting[100];

	for(int i = 0; i<12;i++){
		double d = log10(countts[i]);		// checks the order of magnitude of the number
		if (d<0){
			spaces[i] = 1;					// in case d == -inf (i.e log10(0)), we set the space to be 1
		}
		else{
		spaces[i] = floor(d)+1;				// updates how much space the number needs
		}
	}

	while(1){
		// will construct a string with correct formatting +-----+-----+-----+
		// That will separete the months abvriviations and their counts, as well as upper and lower bounds
		for(int i = 0;i<12;i++){
			formatting[fcnt] = '+';
			fcnt++;

			if(spaces[i] <= 3){
				for(int j = 0;j<5;j++){				//  5 is the default space, so if spaces is <= 3 then default it to 5
					formatting[fcnt] = '-';
					fcnt++;
				}
			}
			else{
				for(int j = 0;j<spaces[i]+2;j++){
					formatting[fcnt] = '-';
					fcnt++;
				}
			}
		}
		formatting[fcnt] = '+';
		formatting[fcnt+1] = '\n';
		formatting[fcnt+2] = '\0';
		break;
	}

	printf("%s",formatting);  									// Upper bound

	for(int i = 0; i<12;i++){
		// Prints Months
		if(spaces[i] <= 3){
			printf("| %s ",months[i]);
		}
		else{
			printf("| %*s%s ",spaces[i]-3,"",months[i]);
		}
	}
	printf("|\n");
	printf("%s",formatting);									// Separator between Abv's and numbers

	for(int i = 0; i<12;i++){
		// Prints Counts per month
		if(spaces[i] <= 3){
			printf("| %*s%d ",spaces[i]-3,"",countts[i]);
		}
		else{
			printf("|%*s%d ",1,"",countts[i]);
		}
	}
	printf("|\n");
	printf("%s",formatting);									// Lower bound
}

void name_const(char* src,int count){
	/*
	Constructs a correct filename with file index
	takes source string and file number 'count'
	*/
	char filenum[8];
	strcpy(src,DATABASE_DIR);								// Coppies directory to strings
	strcat(src,"/");										// Adding '/'  (I assumed that directory will end without '/')	
	sprintf(filenum,"%03i.dat",count);						// sprintf to temp string that takes the data number and converst to string
	strcat(src,filenum);									// strcat the source string with the datanum.dat
}

void* analize_entry(void* trg){
	/*
	Consumer thread function. Takes a target day, month and age.
	The function takes an copies an entry data struct from shared buffer.
		-Updates the month counter for the entry birth month
		-Adds the entry's salary to the sum of salaries
		-Checks if the entry date of birth matches the passed target. 
	 	 If there's a match, it Flags the match and all threads will terminate.
	 	 If no match, will keep consuming untill Producers terminate and no more fresh Data in the buffer.
	*/

	int *target = (int*)trg;
	int month = *(target+2);
	int day = *(target+1);
	int age = *target;
	
	while(1){

		entry temp_entry;
		int entry_month;
	
		sem_wait(&semBufferFull);										// Wait if Buffer is Empty
		pthread_mutex_lock(&mutexBuffer);								// Lock Buffer

		if( winnerFlag || (emptyBufferFlag && (bufferCount<=0))){		// Checks if needs to terminate.
			pthread_mutex_unlock(&mutexBuffer);							// Unlock Buffer
			sem_post(&semBufferFull);									// posts semaphore for in case other consumers are waiting
			pthread_exit(NULL);											// terminates
		}

		memcpy(&temp_entry,&entries[bufferCount-1],sizeof(entry));		// Copy entry		
		bufferCount--;													// Decrement buffer counter
		Consumer_count++;												// Increment Consumers run counter
		pthread_mutex_unlock(&mutexBuffer);								// Unlock Buffer
		sem_post(&semBufferEmpty);										// Increment semaphore


		entry_month = atoi(temp_entry.m);

		pthread_mutex_lock(&mutexMcount);								// Lock mcount
		mcount[entry_month-1]++;										// Increment month count
		salaryAvg += temp_entry.salary;									// Add salary to total fo salaries
		pthread_mutex_unlock(&mutexMcount);								// Unlock mcount

		if(!winnerFlag && (entry_month==month) && (atoi(temp_entry.d)==day) && (2022-atoi(temp_entry.y) == age)){
			winnerFlag = 1;
			memcpy(&winner,&temp_entry,sizeof(entry));
		}
	}
}

void fill_data(entry *temp,char *subtoken,char *rest, int c){
	/*
	Update an entry according to given instruction.
	Given enty struct and a tokenized line from data entry
	According to constant c it will fill the correct entry's variables.
	*/
	switch(c){
		case 0:	
			subtoken = strtok_r(rest,"\n",&rest); subtoken++;
			strcpy(temp->name,subtoken);    			// Update Persons Name

			break;
		case 1:
			subtoken = strtok_r(rest,"\n",&rest); subtoken++;	
			strcpy(temp->address,subtoken);			// Update Persons Address
			break;

		case 2:
			subtoken = strtok_r(rest," \n",&rest); 
			strcpy(temp->phone,subtoken);					// Update Persons Phone digits 1-3
			subtoken = strtok_r(rest," \n",&rest);
			strcpy(temp->phone+3,subtoken);				// Update Persons Phone digits 4-6
			subtoken = strtok_r(rest," \n",&rest); 
			strcpy(temp->phone+6,subtoken);				// Update Persons Phone digits 7-9
			break;

		case 3:
			subtoken = strtok_r(rest,"-\n",&rest); subtoken++;
			strcpy(temp->y,subtoken);				// Update Persons Year of birth

			subtoken = strtok_r(rest,"-\n",&rest);
			strcpy(temp->m,subtoken);				// Update Persons Month of birth

			subtoken = strtok_r(rest,"-\n",&rest);
			strcpy(temp->d,subtoken);				// Update Persons Day of birth
			break;

		case 4:
			subtoken = strtok_r(rest,"\n",&rest); subtoken++;
			strcpy(temp->occupation,subtoken);				// Update Persons occupation
			break;

		case 5:
			subtoken = strtok_r(rest,",\n",&rest); subtoken++;
			temp->salary = atoi(subtoken);				// Update Persons Salary
			break;
	}
}

void* read_entry(){
	/*
	Producer thread function. Takes from Data queue a filename to read.
	The function will read lines from database file. Each line is tokenized and passed with entry struct pointer 
	to fill_data() to fill the data into the entry.
	When the entry is ready, the producer will copy it to a free index in the shared buffer, if no space, will wait.
	When Data queue is empty (i.e. queueCount == -1), will flag that producers wont update the buffer anymore and terminate.
	*/
	char str_buffer[100];
	while(1){

		int c;
		pthread_mutex_lock(&mutexQueue);								// Lock Queue
		file_count++;												
		c = file_count;													// Saves current thread's file number to c
		pthread_mutex_unlock(&mutexQueue);								// Unlock Queue
		char name[dirlen+10];											// Creates string with len directorty len + 10 (for the extra num.dat)
		name_const(name,c);												// Sends the name str to construct the correct filename string for reading

		entry temp_entry;
		FILE* f;

		if(c > DATABASE_SIZE || winnerFlag){
			emptyBufferFlag = 1;
			sem_post(&semBufferFull);									// Increment buffer semaphore in case consumer is struck waiting
			pthread_exit(NULL);
		}

		strcpy(temp_entry.filename,name);			// Coppies the filename from Queue to temp entry filename variable		
		f = fopen(temp_entry.filename, "r");							// Open database entry for reading
		if(f){			
			for(int i = 0;i<6;i++){										// Reads 6 lines of database entry
				fgets(str_buffer,100,f);								// Get line
					char* rest = str_buffer;
					char *token = strtok_r(rest,":",&rest);				// Tokenize line
					fill_data(&temp_entry,token,rest,i);				// Send tokenized line for structure filling
			}
		fclose(f);														// Close file	

		sem_wait(&semBufferEmpty);										// Wait if no space in buffer
		pthread_mutex_lock(&mutexBuffer); 								// Lock buffer

		memcpy(&entries[bufferCount],&temp_entry,sizeof(entry));		// Copying the temp entry memory block to the buffer
		bufferCount++;													// Updating buffer counter
		Producer_count++;
		
		pthread_mutex_unlock(&mutexBuffer);								// Unlock buffer
		sem_post(&semBufferFull);										// Increment buffer fullness semaphore
		}

		else{
			printf("Bad filename: %s\n",temp_entry.filename);
			filesFlag = 1;
			emptyBufferFlag = 1;
			// sem_post(&semBufferFull);									// Increment buffer semaphore in case consumer is struck waiting
			pthread_exit(NULL);
		}
	}
}

int main(int argc, char **argv){
	
	int target[3];							// Array that contains the age, month, day for consumer to mind match to
	target[0] = atoi(*(argv+1));
	char *tkn = strtok(*(argv+2),"-\n");
	target[1] = atoi(tkn);
	tkn = strtok(NULL,"-\n");
	target[2] = atoi(tkn);

	// Threads init
	pthread_t prdcer[PRODUCER_COUNT];
	pthread_t cnsmer[CONSUMER_COUNT];
	// Mutexes init
	pthread_mutex_init(&mutexBuffer,NULL);
	pthread_mutex_init(&mutexQueue,NULL);
	pthread_mutex_init(&mutexMcount,NULL);
	// Semaphores init
	sem_init(&semBufferFull,0,0);
	sem_init(&semBufferEmpty,0,BUFFER_SIZE);
															

	/*_______Threads creation_______*/

	for(int i = 0;i<PRODUCER_COUNT;i++){
		if(pthread_create(&prdcer[i],NULL,&read_entry,NULL) != 0){
			perror("Failed to create PRODUCER\n");
		}
	}

	for(int i = 0;i<CONSUMER_COUNT;i++){
		if(pthread_create(&cnsmer[i],NULL,&analize_entry,target) !=0){
			perror("Failed to create CONSUMER\n");
		}
	}

	/*_______Cleaning up_______*/

	for(int i = 0;i<PRODUCER_COUNT;i++){
		if(pthread_join(prdcer[i], NULL) !=0){
			perror("Failed to join PRODUCER\n");
		}
	}
	for(int i = 0;i<CONSUMER_COUNT;i++){
		if(pthread_join(cnsmer[i], NULL) !=0){
			perror("Failed to join CONSUMER\n");
		}
	}

	//Destroying mutexes and semaphores
	pthread_mutex_destroy(&mutexBuffer);
	pthread_mutex_destroy(&mutexQueue);
	pthread_mutex_destroy(&mutexMcount);
	sem_destroy(&semBufferEmpty);
	sem_destroy(&semBufferFull);

	/*_______Printing_______*/

	printf("#Average Salary: <%d>\n",salaryAvg/Consumer_count);		// devides the total of salaries by the number of consumer runs
	printf("#Month histogram\n");
	prt_histogram(mcount);
	printf("#Found entry:\n");
	if(winnerFlag){
		prt_entry(winner);
	}
	else{
		printf("No entries found!\n");
	}
	printf("Producer_count = %d\nConsumer_count = %d\n",Producer_count,Consumer_count);
	return 0;
}
