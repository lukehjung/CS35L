#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
* function that checks memory and returns if pointer
* is null
*/
void checkmemory(void *input)
{
    if(input == NULL)
    {
        fprintf(stderr, "Memory Error: %d\n", errno);
        exit(1);
    }
}

/*
 * function that checks input and returns if pointer
 * has a error
 */
void checkinput(void *input)
{
    if(ferror(input))
    {
        fprintf(stderr, "IO Error: %d\n", errno);
        exit(1);
    }
}

/*
 * The encoding given in the spec is just an xor of 42
 */
char decoder(const char a)
{
    return (a^42);
}

/*
 * function that goes through two strings to compare
 * if one is larger or less
 */
int frobcmp(char const* a, char const* b)
{
    while(*a != ' ' && *b != ' ')
    {
        if(*a == '\0')
            a++;
        if(*b == '\0')
            b++;
        if (*a == ' ' || decoder(*a) < decoder(*b))
            return -1;
        if (*b == ' ' || decoder(*a) > decoder(*b))
            return 1;
        a++;
        b++;
    }
    return 0;
}

/*
 * function that changes casts the input from a single
 * pointer string to a double
 */
int frbcmp(const void* a, const void* b)
{
    const char* input1 = *(const char**)a;
    const char* input2 = *(const char**)b;
    return frobcmp(input1, input2);
}

/*
 * print function to print out output and checks if input
 * has an error
 */
void print(const char* input)
{
    for(;;)
    {
        putchar(*input);
        checkinput(stdout);
        if(*input++ == ' ')
            return;
    }
}

int main(void)
{
    //initialize variables
    char *input, **output;
    size_t file_size = 10, buffer_size = 0, line_num = 0, line_size = 0, i;
    int eof = feof(stdin);
    int space;

    //create input array and malloc size of the array
    input = (char*) malloc(sizeof(char) * file_size);
    checkmemory(input);

    //continue to parse through string until gets to end of phrase
    while(!eof)
    {
        char c;
        c = getchar();
        checkinput(stdin);
        space = c == ' ';
        eof = feof(stdin);

        //chekcs for space and if line size is 0 to prase
        if(space && ! line_size)
            continue;
        //if our buffer gets to our file size, increase size
        if(buffer_size == file_size)
        {
            file_size *= 2;
            input = (char* ) realloc(input, sizeof(char) * file_size );
            checkmemory(input);
        }

        //continue to add characters to array
        if(!eof)
        {
            input[buffer_size++] = c;
            line_size++;
            if (! space)
                continue;
        }

        //if doesn't pass other cases...
        else 
        {
            //if the size doesn't go up, the input is over
            //need to just return program
            if(buffer_size == 0)
            {
                free(input);
                return 0;
            }

            //if there is no space at the end of buffer, add one
            if(input[buffer_size-1] != ' ')
            {
                input[buffer_size++] = ' ';
            }
            //if end of phrase, breaks out of while loop
            if(line_size == 0)
                break;
        }
        //increment the output size and reset line_size
        line_num ++;
        line_size = 0;
    }
    //output array
    output = (char**) malloc(sizeof(char*) * line_num);
    checkmemory(output);

    //for loop to add characters to array and are
    //separated by spaces for each line
    size_t j;
    char* line = input;
    for( i = 0, j = 0; i < buffer_size; i++)
    {
        if(input[i] == ' ')
        {
            output[j++] = line;
            line = input + i + 1;
        }
    }
    //quick sort the array
    qsort(output, line_num, sizeof(char*), frbcmp);
    for(i = 0; i < line_num; i ++)
    {
        print(output[i]);
    }
    
    //clear variables at end
    free(output);
    free(input);
    return 0;
}
