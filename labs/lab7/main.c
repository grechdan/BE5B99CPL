#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;
int someVariable = 20;

void* ThreadFunction(void* arguments)
{
    pthread_mutex_lock(&lock); //if multiple threads reach here, only one will pass and the others will wait until it is unlocked, then the next will go
   
    someVariable = 50;

    pthread_mutex_unlock(&lock);

    return NULL;
}

void* myThreadFunction(void *arguments){

    
    int* a = (int *)arguments;
    
    printf("Thread running. I am thread: %i\n", *a);


    *a = *a + 1;
    return a;

}

int main(){

	int value = 0;
	int thread_array[5];
    pthread_t thread1;
    pthread_create(&thread1, NULL, myThreadFunction, &value);
    pthread_join(thread1, NULL); 
    printf("Thread running. I am the main thread.\n");
    
    pthread_create(&thread1, NULL, myThreadFunction, &value);
    pthread_join(thread1, NULL); 
    pthread_create(&thread1, NULL, myThreadFunction, &value);
    pthread_join(thread1, NULL); 

    printf("\n\n");


	pthread_t thread2;
	pthread_create(&thread2, NULL, ThreadFunction, &value);
    pthread_join(thread2, NULL);

    return 0;

}