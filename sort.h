#ifndef SORT_H
#define SORT_H 

void   str_write_all  (char** string_buffer, struct Information* file_data);
int    str_write_solo (char* stroka, FILE* filestream);
void   destructor     (struct Information* file_data);
int    comparator1    (char* str1, char* str2);
int    comparator2    (char* str1, char* str2);
void   bubble_sort    (char** array, size_t len, int (*comparator) (char*, char*));
int    str_check      (char* stroka);

#endif 