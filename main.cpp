#include "head.h"
 
/*
[make start] - compile
[make clean] - delete .o files
[make run]   - start program
*/
/*
Description: 
1. Read text Onegin from txt to buffer using calloc
2. Make array of addreses with calloc and write all addreses after \n symbols in buffer orig
3. Make array of strings with calloc like 2. but with checking of "rubbish" like \n\n\n or string: 1. 10/9. and like this
4. Sort array from 3.
5. 3-4. repeat with sort from end to start 
6. write all in file - dictionary.
*/

int main(void)
{   
    struct Information file_data = {
        nullptr,
        nullptr,
        NULL,
        NULL,
        NULL,
        nullptr,
        nullptr,
        nullptr,
    };
    constructor (&file_data);
    destructor  (&file_data);
    return 0;
}