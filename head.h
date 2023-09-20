#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <algorithm>

struct Line {
    size_t len;

    char* start_line;
};

struct Information 
{   
    FILE*  file_text;
    FILE*  file_write;

    size_t size_text;
    size_t n_strings;
    size_t good_strings;

    char* text_buffer;
    Line* string_buffer;
    Line* sort1_buffer;
    Line* sort2_buffer;
};


#include "destructor.h"
#include "constructor.h"

#define FILE_READ  "Onegin.txt"
#define FILE_WRITE "Dictionary_Onegin.txt"

#endif 