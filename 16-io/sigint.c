#include "csapp.h"

void sigint_handler(int sig)
{
    printf("Caught SIGNINT!\n");
    exit(0);
}

int main()
{
    if(signal(SIGINT,sigint_handler)==SIG_ERR)
        unix_error("signal error");
    Pause();
    return 0;
}
