#include"csapp.h"

int mysystem(char * command)
{
    int pid;
    int status;
    char * agrv[4]={"/bin/sh","-c",command,NULL};
    if((pid=Fork())==0)
    {
        execve("/bin/sh",agrv,environ);
    }else
    {
        printf("child pid:%d\n",pid);
        if(waitpid(pid,NULL,0)>0)
        {
            if(WIFEXITED(status))
                printf("exit normally: ");
                return WEXITSTATUS(status);
            if(WIFSIGNALED(status))
                printf("exit by signal: ");
                return WTERMSIG(status);
        }
        
    }
}

int main(int argc, char *argv[])
{
    int code;
    code=mysystem(argv[1]);
    printf("code:%d\n",code);
    return 0;
}
