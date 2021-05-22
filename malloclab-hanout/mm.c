/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "Hunter Team",
    /* First member's full name */
    "Fu Yuan",
    /* First member's email address */
    "1111@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))
/* int value of a void point */
#define INT_VALUE(p) (*(int *)(p))
/*  */
#define BLOCK_LEN(p) (INT_VALUE(p)&(-2))
/* whether or not a block is allocated */
#define IS_ALLOCATED(p) (INT_VALUE(p)&(0x01))

/* move to the next point of list*/
#define LIST_NEXT(p)  ((p)+(INT_VALUE(p)&((int)-2)))


void *list;
void *p;
/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    // printf("init\n");
    mem_sbrk(8);   //unused word(4 bytes) for alignment,one word for the list head
    list = mem_heap_lo()+4;
    INT_VALUE(list)=1;
    return 0;
}

/* simple version of heap check */
int mm_check(void)
{
    void * p=list;
    int i=0;
    printf("heap check--------------\n");
    while(INT_VALUE(p)!=1)
    {
        printf("block %d : ",i);
        if(IS_ALLOCATED(p))
        {
            printf("allocated");
        }else{
            printf("free");
        }
        printf("size: 0x%x",BLOCK_LEN(p));
        printf("  location: 0x%p\n",p);
        p+=BLOCK_LEN(p);
        i+=1;
    }
    printf("-------------------------\n");
    return 0;
}
/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    // printf("malloc 0x%x\n",size);
    int newsize = ALIGN(size + 4);
    p = list;
    int block_len;
    while ((block_len = INT_VALUE(p)) != 1)
    {
        // printf("in while loop \n");
        if (!(IS_ALLOCATED(p)) && block_len >= newsize) //block is free and its size is suitable
        {
            // printf("find suitable block");
            INT_VALUE(p)=newsize+1;
            if(block_len-newsize>=8)    
            {
            //when block have more space than need,split the rest space to a new free block
                INT_VALUE(LIST_NEXT(p))=block_len-newsize;
            }
            return p+4;
        }
        else
        {
            // printf("move to next list point\n");
            p=LIST_NEXT(p);    
        }
    }
    //can't find suitable block in current list
    void *new_block = mem_sbrk(newsize);
    if (new_block == (void *)-1)
        return NULL;
    else
    {
        INT_VALUE(p)=newsize+1;
        INT_VALUE(p+newsize)=1;
        // printf("return by mem_sbrk successfully!\n");
        return new_block;
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    ptr-=4;
    // printf("free %p\n",ptr);
    if(!IS_ALLOCATED(ptr)){
        // printf("already free\n");
        return;
    }
    void *next=LIST_NEXT(ptr);
    if(!IS_ALLOCATED(next)){
        INT_VALUE(ptr)=BLOCK_LEN(ptr)+BLOCK_LEN(next);
    }else
    {
        INT_VALUE(ptr)=BLOCK_LEN(ptr);
    }
    // mm_check();
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *new_block;
    size=ALIGN(size);
    int old_size;
    if(ptr==NULL){
        return malloc(size);
    }
    if(size==0){
        mm_free(ptr);
        return NULL;
    }
    new_block= mm_malloc(size);
    old_size=BLOCK_LEN(ptr-4);
    size=size>old_size?old_size:size;
    for(int i=0;i<size/4;i++){
        INT_VALUE(new_block+i)=INT_VALUE(ptr+i);
    }
    return new_block;
}


