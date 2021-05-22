#include "csapp.h"

int main(int argc, char *argv[],char *env[])
{
    if(execve("/bin/ls",argv,env)<0)
    {
        unix_error("arguement error!\n");
        exit(1);
    }
    return 0;
}