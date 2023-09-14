#include "head.h"

void constructor (struct Information* file_data)
{
	//open files
	file_data -> file_text  = file_rb_open ();
	file_data -> file_write = file_ab_open ();
	//text_buffer
	if ((file_data -> file_text) == nullptr)
	{
		assert(0);
	}
	if ((file_data -> file_write) == nullptr)
	{
		assert(0);
	}
	file_data -> size_text = text_size (file_data -> file_text) + 1; 
	file_data -> text_buffer = nullptr;
	if ((file_data -> text_buffer = (char*) calloc (file_data -> size_text, sizeof (char))) == nullptr)
	{
		assert(0);
	}
	size_t result = fread (file_data -> text_buffer, 1, file_data -> size_text, file_data -> file_text);
	if (result != (file_data -> size_text - 1))
	{
		assert(0);
	}
	*(file_data -> text_buffer + file_data -> size_text - 1) = '\0';
	//string_buffer
	file_data -> n_strings = 0;
	for (size_t i = 0; i < (file_data -> size_text); i++)
    {
        if ((*((file_data -> text_buffer) + i) == 10) || (*((file_data -> text_buffer) + i) == 0))
        {
            file_data -> n_strings += 1;
        }
    }
	file_data -> string_buffer = nullptr;
	if ((file_data -> string_buffer = (char**) calloc (file_data -> n_strings + 1, sizeof (char*))) == nullptr)
	{
		assert(0);
	}
}

FILE* file_rb_open (void)
{
    FILE *file_read = nullptr;
    if ((file_read = fopen (FILE_READ, "rb")) == nullptr) 
    {
        assert(0);
    }
    return file_read;
}

FILE* file_ab_open (void)
{
    FILE *file_write = nullptr;
    if ((file_write = fopen (FILE_WRITE, "ab")) == nullptr) 
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
	if (file_text == nullptr)
	{
		assert(0);
	}
	struct stat st;
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = st.st_size;
	return size_text;
}
