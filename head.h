#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>

FILE* file_r_open (void);
FILE* file_w_open (void);
void file_close (FILE *file_text);
size_t text_size(FILE *file_text);
char* scan_file_buff(FILE *file_text);
char** str_orig_buff(char* text_buffer, size_t len);
char** str_sort1_buff(char** str_orig_buff);
void str_write_solo (char* stroka, FILE* filestream);
void str_write_all (char** str_buffer, FILE* file_write);
int str_compare(char* str1, char* str2);
void bubble_sort(char** array, size_t len);