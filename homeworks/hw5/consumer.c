//----------------------------------------------------------------------------------------
/**
 * \file       consumer.c
 * \author     Daniil Grechany
 * \date       2023/01/02
 * \brief      Consumer
*/
//----------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "global_variables.h"
#include "consumer.h"

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

  int *a = (int*)i;  // extraction thread ID from void pointer
    
  // loop until the exitFlag is raised

  while(exitFlag == 0){


    // checkup of buffer if it is empty

        if(tail == 0){

            sem_wait(&semFilled); // waiting the signal that there is some data in buffer

        }

        // locking the mutex to access buffer

    pthread_mutex_lock(&mutex); 

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

        counterCons++;

        printf("\n--------------------Consumer %i\n", *a);
        printf("--------------------file id: %i\n", tmpPerson.id);
        printf("--------------------salary: %i\n", tmpPerson.salary);
        printf("--------------------year: %i\n", tmpPerson.year);
        printf("--------------------month: %i\n", tmpPerson.month);
        printf("--------------------day: %i\n\n", tmpPerson.day);

        // unlocking the mutex 

        pthread_mutex_unlock(&mutex);   

        // signal that buffer has some space for data

        sem_post(&semEmpty);

        salaryTotal = salaryTotal + tmpPerson.salary;
        histogram[tmpPerson.month - 1]++;

        if(tmpPerson.month == mobPerson && tmpPerson.day == dobPerson && agePerson == 2022 - tmpPerson.year)

          foundID = tmpPerson.id;

        if(tmpPerson.id == 0 && counterCons > DATABASE_SIZE){

            exitFlag = 1;
            pthread_exit(NULL);

        }

    }

}