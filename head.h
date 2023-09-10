#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>

FILE * fileopening (void);
void fileclosing (FILE *file_text);
size_t text_size(FILE *file_text);
char* scan_strfile_buff(FILE *file_text);
void str_sorting(char* text_ptr, size_t len);