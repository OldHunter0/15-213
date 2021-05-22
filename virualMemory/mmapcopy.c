#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> 

int main(int argc, char const *argv[])
{
    if(argc!=2){
        printf("arguement error\n");
        _exit(1);
    }
    FILE* fp= fopen(argv[1],"r");
    

    if(fp==NULL){
        printf("No such file!\n");
        _exit(1);
    }
    int fd =fileno(fp);
    struct stat statbuf;
    stat(argv[1],&statbuf);
    int size=statbuf.st_size;
    char*p= mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);
    write(1,p,size);
    write(1,"\n",1);
    fclose(fp);
    return 0;
}
