#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

/// Inclusion of libraries

#include <pthread.h>  // pthread library
#include <semaphore.h>  // semaphore library

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

extern float salaryAverage;  // average salary, first output
extern int salaryTotal;  // total salaries, to calculate average
extern int personsTotal;  // total amount of persons, to calculate average salary
extern int histogram[MONTHS];  // month histogram, second output
extern int agePerson;  // persons age, who will be "agePerson" years old this year(2022), for search
extern int dobPerson;  // persons day of birth, who will be "agePerson" years old this year(2022) in this day, for search
extern int mobPerson;  // persons month of birth, who will be "agePerson" years old this year(2022) in this month, for search
extern int tail; // last element in the buffer[BUFFER_SIZE]
extern int counterCons;
extern int counterProds;
extern int foundID;  // persons id, who will be "agePerson" years old this year(2022), third output
extern int exitFlag;  // flag which stops consumer threads

/// Declaration of mutex and semaphores

extern pthread_mutex_t mutex;
extern sem_t semFilled;
extern sem_t semEmpty;

#endif
