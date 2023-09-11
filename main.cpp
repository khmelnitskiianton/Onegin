#include "head.h"
 
int main(void)
{   
    FILE *file_text  = file_r_open();
    char* text_buffer = scan_file_buff(file_text);
    
    size_t size_text = text_size(file_text)+1;
    char** orig_buffer = str_orig_buff(text_buffer, size_text);

    char** sort1_buffer = str_sort1_buff(orig_buffer);

    FILE *file_write  = file_w_open();
    str_write_all(orig_buffer, file_write);
    str_write_all(sort1_buffer, file_write);

    free(text_buffer);
    free(sort1_buffer);
    free(orig_buffer);
    file_close (file_text);
    file_close (file_write);
    return 0;
}