#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t lockA, lockB;
int valA = 0;
int valB = 0;
     

void* ThreadFunction(void *arguments){

    int start(){}
    
    if (pthread_mutex_trylock(&lockA) == 0){
        int* pval = arguments;
        int val = pval[0];
        valA = rand();
        printf("Thread: %i\n", val);
        printf("Value A: %i\n", valA);
        printf("\n");
        pthread_mutex_unlock(&lockA);
        return NULL;
    
    } else if(pthread_mutex_trylock(&lockB) == 0){

        int* pval = arguments;
        int val = pval[0];
        valB = rand();
        printf("Thread: %i\n", val);
        printf("Value B: %i\n", valB);
        printf("\n");
        pthread_mutex_unlock(&lockB);
        return NULL;
    
    } else {

        start();

    }


    printf("inside of thread\n");
}

int main()
{

    int* ids = malloc(3*sizeof(int));
    ids[0] = 1;
    ids[1] = 2;
    ids[2] = 3;

    pthread_t t[3];

    pthread_create(&t[0], NULL, ThreadFunction, &ids[0]);
    pthread_create(&t[1], NULL, ThreadFunction, &ids[1]);
    pthread_create(&t[2], NULL, ThreadFunction, &ids[2]);

    printf("Main thread is here.\n");

    pthread_join(t[0], NULL); 
    pthread_join(t[1], NULL); 
    pthread_join(t[2], NULL); 

    free(ids);
    return 0;

}