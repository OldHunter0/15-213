#include "csapp.h"

int main(int argc, char const *argv[])
{
    int index=0;
    printf("0x");
    for (int i = 0; i < 4; i++)
    {
        int left=index;
        while ((char)argv[1][index]!='.')
        {
            index++;
        }
        char* sub_addr;
        strncpy(sub_addr,argv[1],index-left);
        index++;
        printf("%x",atoi(sub_addr));
        if(i<3) printf(".");
        else printf("\n");        
    }
    
}