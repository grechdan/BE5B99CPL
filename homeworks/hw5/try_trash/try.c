char filename[20];
unsigned char buffer[100];
sprintf(filename, "804i. txt",i);
FILE* file = fopen( filename, "r");
fread(buffer,1, 100,file);
fclose(file);
long int a = atoi(buffer);
sum = sum + a;
void *worker(void *i)
  
 int *a = (int*)i;
printf( "Thread %i started \n",*);
for (int i = 0;i<NUM; L++)
        compute(i);
int main( int argc, char* argv[])
numThreads = atoi(argv[1]);
pthread_t thread[numThreads];
 if (numThreads == 0
        printf( "Sequential calculation\n");
        worker(NULL);
}else{
         for (int 0;i<numThreads;i++)
                pthread_create(&thread[o], NULL,worker,&i);
         for (int
                pthread_join(thread[0], NULL);
printf( "The sum across all files is %ld\n", ,sum);
 return 0:
