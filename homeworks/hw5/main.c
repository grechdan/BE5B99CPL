//----------------------------------------------------------------------------------------
/**
 * \file       main.c
 * \author     Daniil Grechany
 * \date       2023/01/02
 * \brief      Data searching and processing
 * 
 * This program is a multi-threaded program that reads data from multiple files and processes the data.
 * 
 * The program has producer and consumer threads. 
 * The producer threads read the data from each file and store the data in a shared buffer.
 * The consumer threads retrieve the data from the buffer and process it.
 * 
 * The program reads data about a person's salary and date of birth from each file, and stores the data in a struct called "Person".
 * The program also calculates and outputs the average salary and a histogram of the number of people born in each month.
 * The program also searches for a person with a matching month and day of birth to a specified age.
 * The program proceeds files from the database, the biggest ammount of files,
 * that the program can proceeds is 999, because we start from 1 and we use %03i.dat" format.
*/
//----------------------------------------------------------------------------------------

/// Inclusion of libraries

#include <stdio.h>  // standart input/output library
#include <stdlib.h>  // standart library functions
#include <string.h>  // string library functions
#include <pthread.h>  // pthread library
#include <semaphore.h>  // semaphore library
//#include "global_variables.h" // global variables
//#include "producer.h" // producer function
//#include "consumer.h" // consumer function

/// Definition of macros

#define BUFFER_SIZE 10  // size of buffer
#define PRODUCER_COUNT 5  // amount of producer threads
#define CONSUMER_COUNT 5  // amount of consumer threads
#define DATABASE_SIZE 100 // amount files in database
#define DATABASE_DIR "database" // directory of the database
#define MONTHS 12 // amount of months in the year

/// Definition of structure Person

typedef struct{

	int id;  // person id, which is the filename with personal data
	int salary;  // persons salary
	int year;  // persons year of birth, YYYY format
	int month;  // persons month of birth, MM format
	int day;  // persons day of birth, DD format

} Person;

/// Declaration of global variables

Person buffer[BUFFER_SIZE]; // buffer, which is used to hold data from producer for consumer threads

int salaryAverage = 0;  // average salary, first output
int salaryTotal = 0;  // total salaries, to calculate average
int personsTotal = 0;  // total amount of persons, to calculate average salary
int histogram[MONTHS] = {0};  // month histogram, second output
int agePerson;  // persons age, who will be "agePerson" years old this year(2022), for search
int dobPerson;  // persons day of birth, who will be "agePerson" years old this year(2022) in this day, for search
int mobPerson;  // persons month of birth, who will be "agePerson" years old this year(2022) in this month, for search
int tail = 0; // last element in the buffer[BUFFER_SIZE]
int counterCons = 0;
int counterProds = 0;
int foundID = 0;  // persons id, who will be "agePerson" years old this year(2022), third output
int exitFlag = 0;  // flag which stops consumer threads
int flagLast = 0;

/// Declaration of mutexes and semaphores

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
sem_t semFilled;
sem_t semEmpty;

/// Declaration of functions

void *producerFunction(void *i);
void *consumerFunction(void *i);
void output();



/// Main function
/**
 * The function gets 3 values as an input: agePerson, dobPerson and mobPerson.
 * Otherwise it prints an error and exits with 1.
 * 
 * After function gets these 3 values and it starts producer and consumer theads and waits till they will finish.
 * 
 * Prints "No entries found!" in case if none of the files contains Person with agePerson, dobPerson and mobPerson.
 * Otherwise it uses the function output to print average salary, histogram and found entity; and returns 0.
 *
 * 
 * \int argc, char* argv[]    amount of inputs, input values;
 * \return 0 
*/

	int main(int argc, char* argv[]){

	// checkup of amount of command line arguments

	if(argc != 3){

		printf("Error: wrong amount of inputs\n");
		exit(1);

	}
		
	agePerson = atoi(argv[1]);  // conversion string argument to integer

	// checkup of correctness of type of the date and extraction of two integers as dobPerson and mobPerson

	if(sscanf(argv[2], "%d-%d", &dobPerson, &mobPerson) != 2){
		
		printf("Error: wrong type of the date\n");
		exit(1);

	}

	//printf("%d\n%d-%d\n\n",agePerson, dobPerson, mobPerson);

	// initialization of mutexes and semaphores

	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	sem_init(&semFilled, 0, BUFFER_SIZE);
	sem_init(&semEmpty, 0, 0);

	// creation of producer threads

	pthread_t producer[PRODUCER_COUNT];
	int f[PRODUCER_COUNT];

	for(int i = 0; i < PRODUCER_COUNT; i++){

	f[i] = i;
	pthread_create(&producer[i],NULL, producerFunction, &f[i]);

	}

	// creation of consumer threads

	pthread_t consumer[CONSUMER_COUNT];
	int ff[CONSUMER_COUNT];

	for(int i = 0; i < CONSUMER_COUNT; i++){

	ff[i] = i;
	pthread_create(&consumer[i],NULL, consumerFunction, &ff[i]);

	}

	// waiting for all producer and consumer threads to finish executing

	for(int i = 0; i < PRODUCER_COUNT; i++){

	  pthread_join(producer[i],NULL);
	  
	}

	for(int i = 0; i < CONSUMER_COUNT; i++){

	  pthread_join(consumer[i],NULL);
	  
	}

	if(foundID == 0){

		printf("No entries found!\n");
		exit(1);

	}

	salaryAverage = (int)salaryTotal / DATABASE_SIZE;

	output();  // call of the function output

	// destruction of semaphores and mutexes

	sem_destroy(&semFilled);
	sem_destroy(&semEmpty);
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);

	return 0;

	}


/// Output function
/**
 * The function outputs an average salary, histogram and found entry
 * 
*/

void output(){

	// output of salaryAverage

	printf("#Average salary: %i\n", salaryAverage);
	
	// output of histogram as a table 

	printf("#Month histogram:\n");

	char *monthsNames[12] = {

    "Jan", "Feb", "Mar", "Apr",
    "May", "Jun", "Jul", "Aug",
    "Sep", "Oct", "Nov", "Dec"
  
	};

	int lengths[MONTHS];

	for (int i = 0; i < MONTHS; i++) {

		char str[10];
		sprintf(str, "%d", histogram[i]);
	int length = strlen(str);
		
		if(length <= 3){

			lengths[i] = 5;

		} else {

			lengths[i] = length + 2;

		}

	}

	for(int i = 0; i < 5; i++){

		for(int j = 0; j < MONTHS; j++){

			if(i == 0 || i == 2 || i == 4){

				printf("+");

			}

			if(i == 1 || i == 3){

				printf("|");

			}

			for(int k = 0; k < lengths[j]; k++){

				if(i == 0 || i == 2 || i == 4){

					printf("-");

				}

				if(i == 1){

					if(lengths[j] > 5){

						if(k < lengths[j] - 4){

							printf(" ");

						}

						if(k == lengths[j] - 4){

							printf("%s ", monthsNames[j]);
							k = k + 3;

						}

					} else {

						printf(" %s ", monthsNames[j]);
						k = 4;

					}

				}

				if(i == 3){

					if(lengths[j] > 5){

						printf(" %i ", histogram[j]);

					} else {

						char str[10];
						sprintf(str, "%d", histogram[j]);
					int length = strlen(str);

						if(k < lengths[j] - length - 1){

							printf(" ");

						}

						if(k == lengths[j] - length - 1){

							printf("%i ", histogram[j]);
							k = lengths[j] - 1;

						}

					}

				}

			}

		}

		if(i == 0 || i == 2 || i == 4){

			printf("+\n");

		}

		if(i == 1 || i == 3){

			printf("|\n");

		}

	}

  	// output of the whole file of the found entry

	char filename[100];
	char line[100];

	printf("#Found entry:\n");

	sprintf(filename, "%s/%03i.dat", DATABASE_DIR, foundID);
	FILE* file = fopen(filename,"r");

	while (fgets(line, sizeof(line), file) != NULL) {

		printf("%s", line);

	}	

	fclose(file);


}


/// Producer function
/**
 * The function gets one input, pointer to the thread number and processes files in the loop using the int i as a name of the file.
 * 
 * After the necessary data is taken from the file, it is written to the temporary structure,
 * and the structure is written to the buffer if there is an empty space. 
 * 
 *
 * \void *i    pointer to the thread number;
 * \return
*/

void *producerFunction(void *i){

    // declaration of variables

    char filename[100];
    char line[100];
    int salary;
    int year, month, day;
    Person tmpPerson;

    int *a = (int*)i;  // extraction thread ID from void pointer
    
    // iteration over files in database

    for(int i = 1; i <= DATABASE_SIZE; i++){

        // checkup if the current file is assigned to this producer thread

        if(*a == i % PRODUCER_COUNT){
                
            // generation of the filename and opening of the file for reading

            sprintf(filename, "%s/%03i.dat", DATABASE_DIR,i); 
            FILE* file = fopen(filename,"r");

            // reading of salary, year, month and day from the file

            while (fgets(line, sizeof(line), file) != NULL) {

              if (strncmp(line, "Salary: ", 8) == 0) {
              
                sscanf(line, "Salary: %d", &salary);
              
              }

              if (strncmp(line, "Date of birth: ", 8) == 0) {
              
                sscanf(line, "Date of birth: %d-%d-%d", &year, &month, &day);
              
              }

            }

            // closing of the file 

            fclose(file);

            // storing data from the file into temporary person struct

            memcpy(&tmpPerson.id, &i, sizeof(int));
            memcpy(&tmpPerson.salary, &salary, sizeof(int));
            memcpy(&tmpPerson.year, &year, sizeof(int));
            memcpy(&tmpPerson.month, &month, sizeof(int));
            memcpy(&tmpPerson.day, &day, sizeof(int));

            // waiting for the empty buffer

            while(tail == BUFFER_SIZE){

              sem_wait(&semEmpty);
            
            }

            // locking the mutex to access buffer

            pthread_mutex_lock(&mutex1);

            // storing data from the temporary person structure into buffer

            memcpy(&buffer[tail],&tmpPerson, sizeof(Person));
            
            // incrementation of tail index of the buffer

            tail = (tail + 1) % BUFFER_SIZE;

            counterProds++;

            // unlocking the mutex 

            pthread_mutex_unlock(&mutex1);

            // signal that buffer has some data 

            sem_post(&semFilled);

        }

    }

    flagLast = 1; 

    return NULL;

}


/// Consumer function
/**
 * The function gets one input, pointer to the thread number and processes buffer till the exitFlag will be raised.
 * 
 * During the run program checks state of the buffer and if it has some data it processes it into global variables:
 * salaryTotal, histogram[MONTHS] and foundID. 
 * If the value of foundID is changed from 0, all threads stop, otherwise they work until files are accessible.
 * 
 * Due to
 * 
 *
 * \void *i    pointer to the thread number;
 * \return
*/

void *consumerFunction(void *i){
    
  // declaration of variables

  Person tmpPerson;

  //int *a = (int*)i;  // extraction thread ID from void pointer
    
  // loop until the exitFlag is raised

  while(exitFlag == 0){


    // checkup of buffer if it is empty

        if(tail == 0){

            sem_wait(&semFilled); // waiting the signal that there is some data in buffer

        }

        // locking the mutex to access buffer

    pthread_mutex_lock(&mutex1); 

    // copying data from buffer to temporary person struct

        memcpy(&tmpPerson, &buffer[tail - 1], sizeof(Person));

        // if buffer is empty

        if(tail == 0){

            // reset buffer

            memset(buffer, 0, sizeof(BUFFER_SIZE));

        }   else {

            // decrement tail index

            tail = (tail - 1) % BUFFER_SIZE;

        }

        personsTotal++;
        // unlocking the mutex 

        pthread_mutex_unlock(&mutex1);   

        // signal that buffer has some space for data

        sem_post(&semEmpty);

        pthread_mutex_lock(&mutex2); 

        salaryTotal = salaryTotal + tmpPerson.salary;
        histogram[tmpPerson.month - 1]++;

        if(tmpPerson.month == mobPerson && tmpPerson.day == dobPerson && agePerson == 2022 - tmpPerson.year)

          foundID = tmpPerson.id;

      	pthread_mutex_unlock(&mutex2); 

        if(tmpPerson.id == 0 && personsTotal > DATABASE_SIZE){

            exitFlag = 1;
            pthread_exit(NULL);

        }

    }

}