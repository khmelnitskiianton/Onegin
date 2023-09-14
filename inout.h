#ifndef INOUT_H
#define INOUT_H 

void   constructor  (struct Information* file_data);
FILE*  file_rb_open  (void);
FILE*  file_ab_open (void);
void   file_close   (FILE *file_text);
size_t text_size    (FILE *file_text);

#endif 