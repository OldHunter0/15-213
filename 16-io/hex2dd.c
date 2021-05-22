#include "csapp.h"

int main(int argc, char const *argv[])
{
    /*     long hex=strtol(argv[1],NULL,16);
    int addr[4];
    for(int i=3;i>=0;i--){
        addr[i]=hex%256;
        hex/=256;
    }
    for(int i=0;i<4;i++){
        printf("%d",addr[i]);
        if(i<3) printf(".");
        else printf("\n");
    } */
    struct in_addr inaddr;
    u_int32_t addr;
    char buf[MAXBUF];
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <hex number>\n", argv[0]);
        exit(0);
    }
    sscanf(argv[1],"%x",&addr);
    inaddr.s_addr=htonl(argv[1]);
    
    if(inet_net_ntop())
    return 0;
}
