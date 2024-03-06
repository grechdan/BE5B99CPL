#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 100
#define PRODUCER_COUNT 5
#define CONSUMER_COUNT 5
#define NUM 100
#define MONTHS 12

typedef struct{

	int id;
	int salary;
	int year;
	int month;
	int day;

} Person;

// Global variables

float salaryAverage = 0;  // Average salary, first output
int salaryTotal = 0;  // Total salaries, to calculate average
int personsTotal = 0;  // Total amount of persons, to calculate average salary
int histogram[MONTHS] = {0};  // Month histogram, second output
int agePerson;  // Persons age, who will be "agePerson" years old this year(2022)
int dobPerson;  // 
int mobPerson;  //
int tail = 0; 
int counterCons = 0;
int counterProds = 0;
Person buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t semFilled;
sem_t semEmpty;

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
	sem_init(&semFilled, 0, BUFFER_SIZE);
	sem_init(&semEmpty, 0, 0);

	pthread_t producer[PRODUCER_COUNT];
	int f[PRODUCER_COUNT];

  for(int i = 0; i < PRODUCER_COUNT; i++){

    f[i] = i;
    pthread_create(&producer[i],NULL, producerFunction, &f[i]);

  }

  pthread_t consumer[CONSUMER_COUNT];
	int ff[CONSUMER_COUNT];

  for(int i = 0; i < CONSUMER_COUNT; i++){

    ff[i] = i;
    pthread_create(&consumer[i],NULL, consumerFunction, &ff[i]);

  }

  for(int i = 0; i < PRODUCER_COUNT; i++){

	  pthread_join(producer[i],NULL);
	  
	}

	for(int i = 0; i < CONSUMER_COUNT; i++){

	  pthread_join(consumer[i],NULL);
	  
	}
	
	for(int i = 0; i < BUFFER_SIZE; i++){

		printf("\nBuffer%i\n", i);
		printf("file id: %i\n", buffer[i].id);
		printf("salary: %i\n", buffer[i].salary);
		printf("year: %i\n", buffer[i].year);
		printf("month: %i\n", buffer[i].month);
		printf("day: %i\n\n", buffer[i].day);
	  
	}

	printf("counterCons: %i\ncounterProds: %i\n", counterCons, counterProds);
	printf("Fine\n");
	
	sem_destroy(&semFilled);
	sem_destroy(&semEmpty);
	pthread_mutex_destroy(&mutex);

	return 0;
}


void *producerFunction(void *i){

	char filename[20];
	char line[100];
	int salary;
	int year, month, day;
	Person tmpPerson;

	int *a = (int*)i;
	
	for(int i = 1; i <= NUM; i++){

		if(*a == i % PRODUCER_COUNT){
		
			sprintf(filename, "%03i.dat",i); 
			FILE* file = fopen(filename,"r");

			while (fgets(line, sizeof(line), file) != NULL) {

				if (strncmp(line, "Salary: ", 8) == 0) {
				
					sscanf(line, "Salary: %d", &salary);
				
				}

				if (strncmp(line, "Date of birth: ", 8) == 0) {
				
					sscanf(line, "Date of birth: %d-%d-%d", &year, &month, &day);
				
				}

			}

			fclose(file);

			memcpy(&tmpPerson.id, &i, sizeof(int));
			memcpy(&tmpPerson.salary, &salary, sizeof(int));
			memcpy(&tmpPerson.year, &year, sizeof(int));
			memcpy(&tmpPerson.month, &month, sizeof(int));
			memcpy(&tmpPerson.day, &day, sizeof(int));

			sem_wait(&semEmpty);

			pthread_mutex_lock(&mutex);

			memcpy(&buffer[tail],&tmpPerson, sizeof(Person));
			

			printf("\nProducer %i\n", *a);
			printf("file id: %i\n", buffer[tail].id);
			printf("salary: %i\n", buffer[tail].salary);
			printf("year: %i\n", buffer[tail].year);
			printf("month: %i\n", buffer[tail].month);
			printf("day: %i\n\n", buffer[tail].day);

			tail = (tail + 1) % BUFFER_SIZE;

			counterProds++;

			pthread_mutex_unlock(&mutex);

			sem_post(&semFilled);

		}

	} 

}


void *consumerFunction(void *i){

	int id, salary;
	int year, month, day;
	Person tmpPerson;
	int *a = (int*)i;
	
	for(int i = 0; i < NUM; i++){

		if(*a == i % CONSUMER_COUNT){

			sem_wait(&semFilled);

			pthread_mutex_lock(&mutex);	

			memcpy(&tmpPerson, &buffer[tail - 1], sizeof(Person));

			tail = (tail - 1);

			counterCons++;

			printf("\nConsumer %i\n", *a);
			printf("file id: %i\n", tmpPerson.id);
			printf("salary: %i\n", tmpPerson.salary);
			printf("year: %i\n", tmpPerson.year);
			printf("month: %i\n", tmpPerson.month);
			printf("day: %i\n\n", tmpPerson.day);

			pthread_mutex_unlock(&mutex);		

			sem_post(&semEmpty);	

		}
			
	}

}
