#include <pthread.h>
#include <stdio.h>

typedef struct thread_data{
    int threadId;
    char name[20];
    //..
}ThreadData;
typedef char caracter;

void * holaMUndo(void *arg){
    ThreadData *myData = (ThreadData *)arg;
    printf("HOla desde el hilo y mi id es %d\n",myData->threadId);
    pthread_exit(NULL);
}

int main(){
    for(int i = 0; i < 100; i++){
        ThreadData myData;
        pthread_t threadId;
        myData.threadId = 1;
        pthread_create(&threadId, NULL, holaMUndo,(void *) &myData);
    }
    pthread_exit(NULL);
    printf("NUNCA LLEGA\n");
    return 0;
}