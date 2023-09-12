#include "head.h"

FILE* file_r_open (void)
{
    FILE *file_read = nullptr;
    if ((file_read = fopen (FILE_READ, "rb")) == nullptr) 
    {
        assert(0);
    }
    return file_read;
}

FILE* file_w_open (void)
{
    FILE *file_write = nullptr;
    if ((file_write = fopen (FILE_WRITE, "wb")) == nullptr) 
    {
        assert(0);
    }
    return file_write;
}

void file_close (FILE *file_text)
{
	if (fclose (file_text) != 0)
	{
		assert(0);
	}
}

size_t text_size (FILE *file_text)
{
	struct stat st;
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = st.st_size;
	return size_text;
}

char* scan_file_buff (FILE *file_text)
{
	size_t size_text = text_size (file_text) + 1; //1 byte for end of array
	char *text_buffer = nullptr;
	if ((text_buffer = (char*) calloc (size_text, sizeof(char))) == nullptr)
	{
		assert(0);
	
	}
	size_t result = fread (text_buffer, 1, size_text, file_text);
	if (result != (size_text - 1))
	{
		assert(0);
	}
	*(text_buffer + size_text - 1) = '\0';

	return text_buffer;
}

char** str_orig_buff (char* text_buffer, size_t len)
{
	size_t size_text = len;
	size_t n_strok = 0;
	for (size_t i = 0; i < size_text; i++)
    {
        if ((*(text_buffer + i) == 10) || (*(text_buffer + i) == 0))
        {
            n_strok += 1;
        }
    }
	char **str_buffer = nullptr;
	if ((str_buffer = (char**) calloc (n_strok + 1, sizeof(char*))) == nullptr)
	{
		assert(0);
	}

	char *symbol = text_buffer;
	size_t i = 0;
	size_t amount = 1;
	*(str_buffer) = text_buffer;
	while (*(symbol + i) != '\0')
	{
		if ((*(symbol + i) == 10) && (*(symbol + i + 1) != '\0'))
		{
			*(str_buffer + amount) = symbol + i + 1; //следующий за \n 
			amount++;
		}
		i++;
	}
	if (*(str_buffer + amount) != 0)
	{
		assert(0);
	}
	return str_buffer;
}

int str_write_solo (char* stroka, FILE* filestream)
{
    size_t i = 0;
    int x = 0;
	while (*(stroka + i) != '\0')
    { 
		if((x = putc (*(stroka + i), filestream)) == EOF)
		{
			assert(0);
		}
		if (x == '\n') 
		{
			break;
		}
        i++;
    }
	return 0;
}

void str_write_all (char** str_buffer, FILE* file_write)
{
	size_t i = 0;
	while (*(str_buffer + i) != nullptr)
	{
		str_write_solo (*(str_buffer + i), file_write);
		i++;
	}
	fprintf(file_write, "--------------------------------------------------------------------------------------------------------------------------------------------------------"
						"\n--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

