#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM 10000

long int sum = 0;
int numThreads = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;


void compute(int i){
  
  char filename[20];
  unsigned char buffer[100];
  sprintf(filename, "%04i.txt",i);
  FILE* file = fopen(filename, "r");
  fread(buffer,1,100,file);
  fclose(file);
  long int a = atoi(buffer);
  pthread_mutex_lock(&mutex);
  sum = sum + a;
  pthread_mutex_unlock(&mutex);

}


void *worker(void *i){

  int *a = (int*)i;
  printf("Thread %i started\n", *a);
  for(int i = 0; i < NUM; i++){

    if (*a == i%numThreads) compute(i);
    if (i == NUM/2) pthread_cond_signal(&cond);

  }

}

void *notify(void *i){
	
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);
	printf("Half life %ld\n", sum);
	pthread_mutex_unlock(&mutex);

}

int main(int argc, char* argv[]){

  numThreads = atoi(argv[1]);
  pthread_t thread[numThreads];
  pthread_t notif;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  if(numThreads == 0){

    printf("Sequential calculation\n");
    worker(NULL);

  } else {

    int f[numThreads];
    pthread_create(&notif,NULL, notify, NULL);
    for(int i = 0; i < numThreads; i++){

      f[i] = i;
      pthread_create(&thread[i],NULL, worker, &f[i]);

    }

    for(int i = 0; i < numThreads; i++){

      pthread_join(thread[i],NULL);
      
    }
    

  }

  
  printf("The result is: %ld\n", sum);
  return 0;

}
