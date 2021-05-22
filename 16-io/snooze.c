#include "csapp.h"
unsigned int secs,rd;
unsigned int snooze(unsigned int secs){
    rd=sleep(secs);
    printf("Slept for %d of %d secs\n",secs-rd,secs);
    return rd;
}

void signal_handler(int sig)
{
    return;
}

int main(int argc, char const *argv[])
{
    if(argc!=2) {
        fprintf(stderr,"usage: %s <secs>\n",argv[0]);
        exit(0);
    }
    secs=atoi(argv[1]);
    if(signal(SIGINT,signal_handler)==SIG_ERR)
        unix_error("signal error");
    snooze(secs);
    return 0;
}
