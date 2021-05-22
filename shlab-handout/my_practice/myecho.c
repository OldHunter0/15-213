#include<stdio.h>

int main(int argc, char const *argv[],char *envp[])
{
    printf("commandline arguements:\n");
    for(int i=0;i<argc;i++){
        printf("argv[%d]:%s\n",i,argv[i]);
    }
    printf("Environment variables:\n");
    int i=0;
    while ((char*)envp[i]!=NULL)
    {
        printf("envp[%d]:%s\n",i,envp[i]);
        i++;
        /* code */
    }
    
    exit(0);
}
