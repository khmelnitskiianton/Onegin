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
	if ((file_data -> string_buffer  = (Line*) calloc (file_data -> n_strings + 1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}



	//string_buffer
	char *symbol = file_data -> text_buffer;
	size_t p = 0;
	size_t amount = 1;
	size_t length = 0;
	(*(file_data -> string_buffer)).start_line = file_data -> text_buffer;
	while (*(symbol + p) != '\0')
	{
		length++;
		if ((*(symbol + p) == 10) && (*(symbol + p + 1) != '\0'))
		{
			(*(file_data -> string_buffer + amount)).start_line = symbol + p + 1;
			(*(file_data -> string_buffer + amount)).len = length;
			amount++;
			length = 0;
		}
		p++;
	}
	if ((*(file_data -> string_buffer + amount)).start_line != NULL)
	{
		assert(0);
	}
	//sort1_buffer and sort2_buffer
	file_data -> good_strings = 0;
	size_t all = 0;
	while ((*(file_data -> string_buffer + all)).start_line != nullptr)
	{
		if (str_check ((*(file_data -> string_buffer + all)).start_line))
		{
			all++;
			continue;
		}
		(file_data -> good_strings)++;
		all++;
	}
	(file_data -> good_strings)++;
	if ((file_data -> sort1_buffer = (Line*) calloc (file_data -> good_strings + 1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}
	if ((file_data -> sort2_buffer = (Line*) calloc (file_data -> good_strings + 1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}
	size_t shift = 0;
	for (size_t i = 0; i < file_data -> n_strings; i++)
	{	
		if (str_check ((*(file_data -> string_buffer + i)).start_line))
		{
			continue;
		}
		(*(file_data -> sort1_buffer + shift)).start_line = (*(file_data -> string_buffer + i)).start_line;
		(*(file_data -> sort2_buffer + shift)).start_line = (*(file_data -> string_buffer + i)).start_line;

		(*(file_data -> sort1_buffer + shift)).len = (*(file_data -> string_buffer + i)).len;
		(*(file_data -> sort2_buffer + shift)).len = (*(file_data -> string_buffer + i)).len;
		shift++;
	}

	bubble_sort (file_data -> sort1_buffer, file_data -> good_strings, comparator1);
	bubble_sort (file_data -> sort2_buffer, file_data -> good_strings, comparator2);

	str_write_all (file_data -> string_buffer, file_data);
    str_write_all (file_data -> sort1_buffer,  file_data);
    str_write_all (file_data -> sort2_buffer,  file_data);
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

void str_write_all (Line* string_buffer, struct Information* file_data)
{
	size_t i = 0;
	while ((*(string_buffer + i)).start_line != nullptr)
	{
		str_write_solo ((*(string_buffer + i)).start_line, file_data -> file_write);
		i++;
	}
	fprintf(file_data -> file_write, "\n\n--------------------------------------------------------------------------------------------------------------------------------------------------------"
						               "\n--------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void bubble_sort (Line* sort_buffer, size_t len, int (*comparator) (Line, Line))
{
	char* ptr = nullptr;
	for (size_t i = 0; i < (len - 2); i++)
	{
		for (size_t j = i+1; j < (len - 1); j++)
		{
			if (comparator (*(sort_buffer + i), *(sort_buffer + j))) 
			{
				ptr = (*(sort_buffer + j)).start_line;
				(*(sort_buffer + j)).start_line = (*(sort_buffer + i)).start_line;
				(*(sort_buffer + i)).start_line = ptr;
			}
		}
	}
}

int comparator1 (Line str1, Line str2)
{
	size_t i  = 0;
	size_t j  = 0;
	int not_letter1 = 0; 
	int not_letter2 = 0;
	while ((*(str1.start_line + i) != '\0') && (*(str1.start_line + i) != '\n') && (*(str2.start_line + j) != '\0') && (*(str2.start_line + j) != '\n'))
	{
		if (((*(str1.start_line + i) < 97) || (*(str1.start_line + i) > 122)) && ((*(str1.start_line + i) < 65) || (*(str1.start_line + i) > 90)))
		{
			not_letter1 = 0;
			i++;
		}
		else
		{
			not_letter1 = 1;
		}
		if (((*(str2.start_line + j) < 97) || (*(str2.start_line + j) > 122)) && ((*(str2.start_line + j) < 65) || (*(str2.start_line + j) > 90)))
		{
			not_letter2 = 0;
			j++;
		}
		else
		{
			not_letter2 = 1;
		}
		if (not_letter1 && not_letter2)
		{
			if      (tolower (*(str1.start_line + i)) > tolower (*(str2.start_line + j)))
			{
				return 1;
			}
			else if (tolower (*(str1.start_line + i)) < tolower (*(str2.start_line + j)))
			{
				return 0;
			}
			else
			{
				i++;
				j++;
			}
		}
	}
	return 1;
}

int comparator2 (Line str1, Line str2)
{
	size_t i = str1.len;
	size_t j = str2.len;
	int not_letter1 = 0;
	int not_letter2 = 0;
	while ((i != 0) && (j != 0))
	{
		if (((*(str1.start_line + i) > 97) && (*(str1.start_line + i) < 122)) || ((*(str1.start_line + i) > 65) && (*(str1.start_line + i) < 90)))
		{
			not_letter1 = 1;
		}
		else
		{
			not_letter1 = 0;
			i--;
		}
		if (((*(str2.start_line + j) > 97) && (*(str2.start_line + j) < 122)) || ((*(str2.start_line + j) > 65) && (*(str2.start_line + j) < 90)))
		{
			not_letter2 = 1;
		}
		else
		{
			not_letter2 = 0;
			j--;
		}
		if (not_letter1 && not_letter2)
		{
			if      (tolower (*(str1.start_line + i)) > tolower (*(str2.start_line + j)))
			{
				return 1;
			}
			else if (tolower (*(str2.start_line + i)) < tolower (*(str2.start_line + j)))
			{
				return 0;
			}
			else
			{
				i--;
				j--;
			}
		}
	}
	return 0;
}

int str_check (char* stroka)
{
	size_t len = 0;
	while ((*(stroka + len) != '\0') && (*(stroka + len) != '\n'))
	{
		if (((*(stroka + len) > 97) && (*(stroka + len) < 122)) || ((*(stroka + len) > 65) && (*(stroka + len) < 90)))
		{
			return 0;
		}
		len++;
	}
	return 1;
}