#include <stdio.h>

int main(){
    FILE *lsOutput;
    FILE *tomayInput;
    char readBuffer[80];
    lsOutput = popen("ls *.c","r");
    tomayInput = popen("./tomay","w");
    int count=0;
    while(fgets(readBuffer,80,lsOutput)){
        fputs(readBuffer,tomayInput);
        count+=1;
    }
    pclose(lsOutput);
    pclose(tomayInput);
    printf("%d\n",count);
}