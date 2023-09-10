#include "head.h"

#define TEXT_FILE "Onegin_cut.txt" 

FILE* fileopening (void)
{
    FILE *file_text = nullptr;
    if ((file_text = fopen (TEXT_FILE, "rb")) == nullptr) 
    {
        assert(0);
    }
    return file_text;
}
void fileclosing (FILE *file_text)
{
	if (fclose(file_text) != 0)
	{
		assert(0);
	}
}
size_t text_size(FILE *file_text)
{
	struct stat st;
    int fd = fileno(file_text); 
    fstat(fd, &st);
    size_t size_text = st.st_size;
	return size_text;
}

char* scan_strfile_buff(FILE *file_text)
{
	size_t size_text = text_size(file_text) + 1; //1 byte for end of array
	char *text_ptr = nullptr;
	if ((text_ptr = (char*) calloc(size_text, sizeof(char))) == nullptr)
	{
		assert(0);
	
	}
	size_t result = fread(text_ptr, 1, size_text, file_text);
	if (result != (size_text - 1))
	{
		assert(0);
	}
	*(text_ptr + size_text - 1) = '\0';
	return text_ptr;
	fileclosing (file_text);
}

void str_sorting(char* text_ptr, size_t len)
{
	size_t size_text = len;
	size_t n_strok = 0;
	for (size_t i = 0; i < size_text; i++)
    {
        if ((*(text_ptr + i) == 10)||(*(text_ptr + i) == 0))
        {
            n_strok += 1;
        }
    }
	char **buffer = nullptr;
	if ((buffer = (char**) calloc(n_strok, sizeof(char))) == nullptr)
	{
		assert(0);
	}
	//while (text_ptr)
	printf("%d", n_strok);
}

