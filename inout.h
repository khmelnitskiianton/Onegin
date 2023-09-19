#ifndef INOUT_H
#define INOUT_H 

void   constructor    (struct Information* file_data);
FILE*  file_rb_open   (void);
FILE*  file_ab_open   (void);
void   file_close     (FILE *file_text);
size_t text_size      (FILE *file_text);
void   str_write_all  (Line* string_buffer, struct Information* file_data);
int    str_write_solo (char* stroka, FILE* filestream);
int    comparator1    (Line str1, Line str2);
int    comparator2    (Line str1, Line str2);
void   bubble_sort    (Line* sort_buffer, size_t len, int (*comparator) (Line, Line));
int    str_check      (char* stroka);

#endif 