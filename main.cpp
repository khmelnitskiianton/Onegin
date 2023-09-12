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
    FILE*  file_text    = file_r_open ();
    char*  text_buffer  = scan_file_buff (file_text);
    size_t size_text    = text_size (file_text) + 1;
    char** orig_buffer  = str_orig_buff (text_buffer, size_text);

    char** sort1_buffer = str_sort1_buff (orig_buffer);
    char** sort2_buffer = str_sort2_buff (orig_buffer);

    FILE* file_write = file_w_open ();
    str_write_all (orig_buffer,  file_write);
    str_write_all (sort1_buffer, file_write);
    str_write_all (sort2_buffer, file_write);

    free (text_buffer);
    free (orig_buffer);
    free (sort1_buffer);
    free (sort2_buffer);

    file_close (file_text);
    file_close (file_write);

    return 0;
}