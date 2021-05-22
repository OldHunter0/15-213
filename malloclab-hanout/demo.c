#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

#define INT_VALUE(p) (*(int *)(p))

int main(int argc, char const *argv[])
{
    int a=10;
    void *pa=&a;
    INT_VALUE(pa)=20;
    printf("%d\n",a);
    return 0;
}
