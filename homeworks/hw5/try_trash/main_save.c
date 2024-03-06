#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 100
#define PRODUCER_COUNT 5
#define CONSUMER_COUNT 5
#define NUM 100
#define MONTHS 12

// Global variables

float salaryAverage = 0;  // Average salary, first output
int salaryTotal = 0;  // Total salaries, to calculate average
int personsTotal = 0;  // Total amount of persons, to calculate average salary
int histogram[MONTHS] = {0};  // Month histogram, second output
int agePerson;  // Persons age, who will be "agePerson" years old this year(2022)
int dobPerson;  // 
int mobPerson;  //
int buffer[BUFFER_SIZE];
int tail = 0; 
int counter = 1;

pthread_mutex_t mutex;
pthread_cond_t cond;

void *producerFunction(void *i);
void *consumerFunction(void *i);


// Main function,

int main(int argc, char* argv[]){
	
	// Parse command line arguments
	if(argc != 3){

		printf("Error: wrong amount of inputs\n");
    	exit(1);
  	}
  	
  	agePerson = atoi(argv[1]);
  	
  	if(sscanf(argv[2], "%d-%d", &dobPerson, &mobPerson) != 2){
    	
    	printf("Error: wrong type of the date\n");
    	exit(1);
	}

	printf("%d\n%d-%d\n\n",agePerson, dobPerson, mobPerson);

	pthread_mutex_init(&mutex, NULL);

	pthread_t producer[PRODUCER_COUNT];
	int ff[PRODUCER_COUNT];

	for(int i = 0; i < PRODUCER_COUNT; i++){

		ff[i] = i;
		pthread_create(&producer[i],NULL, producerFunction, &ff[i]);

	}

	for(int i = 0; i < PRODUCER_COUNT; i++){

		pthread_join(producer[i],NULL);

	}

	for(int i = 0; i < BUFFER_SIZE; i++){

		printf("%d\n", buffer[i]);

	}

	printf("Fine\n");

	return 0;
}

void *producerFunction(void *i){

	char filename[20];
	char line[100];
	int salary;
	int year, month, day;

	int *a = (int*)i;
	
	for(int i = 1; i <= 20; i++){

  	if(*a == i % PRODUCER_COUNT){

		sprintf(filename, "%03i.dat",i);
		FILE* file = fopen(filename,"r");

		while (fgets(line, sizeof(line), file) != NULL) {

			// Check if the line starts with "Salary: "
			if (strncmp(line, "Salary: ", 8) == 0) {
			
				// Extract the salary amount
				sscanf(line, "Salary: %d", &salary);
			
			}

			// Check if the line starts with "Date of birth: "
			if (strncmp(line, "Date of birth: ", 8) == 0) {
			
				// Extract the date of birth
				sscanf(line, "Date of birth: %d-%d-%d", &year, &month, &day);
			
			}

		}

		// Close the file
		fclose(file);

		pthread_mutex_lock(&mutex);

		buffer[tail] = i;
		buffer[tail + 1] = salary;
		buffer[tail + 2] = year;
		buffer[tail + 3] = month;
		buffer[tail + 4] = day;

		tail = (tail + 5);
		printf("%d\n", buffer[tail]);
		printf("%d\n", buffer[tail+1]);
		printf("%d\n", buffer[tail+2]);
		printf("%d\n", buffer[tail+3]);
		printf("%d\n", buffer[tail+4]);
		printf("producer%i started\n", *a);

		pthread_mutex_unlock(&mutex);
  		
  	}

	}

}
