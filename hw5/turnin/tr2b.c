#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void error()
{
    fprintf(stderr, "Incorrect Input... %d\n", errno);
    exit(1);
}
int main(int argc, const char* input2[])
{
    if(argc !=3)
    {
        error();
    }
    const char* arg1 = input2[1];
    const char* arg2 = input2[2];
    if(strlen(arg1) != strlen(arg2))
    {
        error();
    }
    
    size_t len = strlen(arg1);
    for(int i = 0; i < len-1; i ++)
    {
        for(int j = i+1; j < len; j ++)
            if(arg1[i] == arg1[j])
                error();
    }
    
    int eof = feof(stdin);
    int change;
    while(!eof)
    {
        char c;
        c=getchar();
        eof = feof(stdin);
        
        if(eof)    
     		break;
        for(int i = 0; i < len; i ++)
        {
            if(c == arg1[i])
            	c = arg2[i];
        }
         putchar(c);
    }
}
