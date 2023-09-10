#include "head.h"
 
int main(void)
{   
    FILE *file_text  = fileopening();
    char* text_ptr = scan_strfile_buff(file_text);
    size_t size_text = text_size(file_text)+1;
    /*
    size_t counter = 0;
    for (size_t i = 0; i < size_text; i++)
    {
        if ((*(text_ptr + i) == 10)||(*(text_ptr + i) == 0))
        {
            counter += 1;
        }
        printf("%d ", *(text_ptr + i));
    }
    printf("\n %d", counter);
    */
   str_sorting(text_ptr, size_text);
}