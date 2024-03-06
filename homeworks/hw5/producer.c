//----------------------------------------------------------------------------------------
/**
 * \file       producer.c
 * \author     Daniil Grechany
 * \date       2023/01/02
 * \brief      Producer
*/
//----------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "global_variables.h"
#include "producer.h"

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

            pthread_mutex_lock(&mutex);

            // storing data from the temporary person structure into buffer

            memcpy(&buffer[tail],&tmpPerson, sizeof(Person));
            

            printf("\n-----Producer %i\n", *a);
            printf("-----file id: %i\n", buffer[tail].id);
            printf("-----salary: %i\n", buffer[tail].salary);
            printf("-----year: %i\n", buffer[tail].year);
            printf("-----month: %i\n", buffer[tail].month);
            printf("-----day: %i\n\n", buffer[tail].day);

            // incrementation of tail index of the buffer

            tail = (tail + 1) % BUFFER_SIZE;

            counterProds++;

            // unlocking the mutex 

            pthread_mutex_unlock(&mutex);

            // signal that buffer has some data 

            sem_post(&semFilled);

        }

    } 

}