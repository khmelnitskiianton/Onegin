FILE* file_r_open (void);
FILE* file_w_open (void);
void file_close (FILE *file_text);
size_t text_size(FILE *file_text);
char* scan_file_buff(FILE *file_text);
char** str_orig_buff(char* text_buffer, size_t len);