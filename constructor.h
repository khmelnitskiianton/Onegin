#ifndef INOUT_H
#define INOUT_H 

int    constructor      (struct Information* file_data);
FILE*  file_rb_open     (void);
FILE*  file_ab_open     (void);
int    file_close       (FILE *file_text);
size_t text_size        (FILE *file_text);
int    str_write_all    (const Line* string_buffer, struct Information* file_data);
int    str_write_solo   (const char* stroka, FILE* filestream);
int    comparator_start (const void* str11, const void* str22);
int    comparator_end   (const void* str11, const void* str22);
int    bubble_sort      (void* sort_buffer, const size_t len, const size_t size_one, int (*comparator) (const void*, const void*));
int    str_check        (const char* stroka);
int    change_elements  (void* elem1, void* elem2, const size_t size_one);

#endif 