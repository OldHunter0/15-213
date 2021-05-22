#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int snooze(unsigned int secs){
    printf("Slept for 0 of %d \n",secs);
    for(int i=0;i<secs;i++){
        sleep(1);
        printf("Slept for %d of %d\n",i+1,secs);
    }
    return 0;
}

unsigned int snooze2(unsigned int secs){
    unsigned int rd=sleep(secs);
    printf("Slept for %d of %d secs\n",secs-rd,secs);
    return rd;
}
int main(int argc,const char** argv)
{
    snooze2(atoi(argv[1]));
    /* code */
    return 0;
}
