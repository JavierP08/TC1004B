#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void hola(int signalNumb){
    printf("Recibi la señal %d\n",signalNumb);
}

int cond;

void termine(int sigNumber){
    printf("Terminando while\n");
    cond = 0;
}

int main(){
    signal(12,termine);
    signal(2,hola);
    cond = 1;
    while(cond == 1){
        printf("trabajando\n");
        sleep(1);
        
    }
    printf ("Aqui nunca llega\n");
    return 0;
}