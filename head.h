#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>

struct Information 
{   
    FILE*  file_text;
    FILE*  file_write;
    size_t size_text;
    size_t n_strings;
    size_t good_strings;
    char*  text_buffer;
    char** string_buffer;
    char** sort1_buffer;
    char** sort2_buffer;
};

#include "sort.h"
#include "inout.h"

#define FILE_READ  "Onegin_cut.txt"
#define FILE_WRITE "Dictionary_Onegin.txt"

#endif 