#include "head.h"

int constructor (struct Information* file_data)
{
	//open files
	file_data -> file_text  = file_rb_open ();
	file_data -> file_write = file_ab_open ();
	//text_buffer
	if (!(file_data -> file_text))
	{
		assert(0);
	}
	if (!(file_data -> file_write))
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
	if ((file_data -> string_buffer  = (Line*) calloc (file_data -> n_strings+1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}
	//string_buffer
	char *symbol = file_data -> text_buffer;
	size_t p = 0;
	size_t amount = 0;
	size_t length = 0;
	(*(file_data -> string_buffer)).start_line = file_data -> text_buffer;
	while (*(symbol + p) != '\0')
	{
		length++;
		if ((*(symbol + p) == 10) && (*(symbol + p + 1) != '\0'))
		{
			(*(file_data -> string_buffer + amount)).len = length-2;
			amount++;
			length = 0;
			(*(file_data -> string_buffer + amount)).start_line = symbol + p + 1;
		}
		p++;
	}
	(*(file_data -> string_buffer + amount)).len = length;
	amount++;                                              
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

	if ((file_data -> sort1_buffer = (Line*) calloc (file_data -> good_strings + 1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}
	if ((file_data -> sort2_buffer = (Line*) calloc (file_data -> good_strings + 1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}
	size_t shift = 0;
	for (size_t i = 0; i < (file_data -> n_strings); i++)
	{	
		if (str_check ((*(file_data -> string_buffer + i)).start_line))
		{
			continue;
		}
		(*(file_data -> sort1_buffer + shift)).start_line = (*(file_data -> string_buffer + i)).start_line;
		(*(file_data -> sort2_buffer + shift)).start_line = (*(file_data -> string_buffer + i)).start_line;

		(*(file_data -> sort1_buffer + shift)).len        = (*(file_data -> string_buffer + i)).len;
		(*(file_data -> sort2_buffer + shift)).len        = (*(file_data -> string_buffer + i)).len;
		shift++;
	}
	(file_data -> sort1_buffer + shift) -> start_line = nullptr;
	(file_data -> sort2_buffer + shift) -> start_line = nullptr;
	(file_data -> sort1_buffer + shift) -> len        = NULL;
	(file_data -> sort2_buffer + shift) -> len        = NULL;

	bubble_sort (file_data -> sort1_buffer, file_data -> good_strings, sizeof(Line), comparator_start);
	bubble_sort (file_data -> sort2_buffer, file_data -> good_strings, sizeof(Line), comparator_end);
	//qsort (file_data -> sort1_buffer, file_data -> good_strings, sizeof(Line), comparator_start);
	//qsort (file_data -> sort2_buffer, file_data -> good_strings, sizeof(Line), comparator_end);

	str_write_all (file_data -> string_buffer, file_data);
    str_write_all (file_data -> sort1_buffer,  file_data);
    str_write_all (file_data -> sort2_buffer,  file_data);

	return 1;
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

int file_close (FILE *file_text)
{
	if (!file_text)
	{
		assert(0);
	}
	if (fclose (file_text) != 0)
	{
		assert(0);
	}
	return 1;
}

size_t text_size (FILE *file_text)
{
	if (!file_text)
	{
		assert(0);
	}
	struct stat st;
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = st.st_size;
	return size_text;
}

int str_write_solo (const char* stroka, FILE* filestream)
{
	if (!filestream)
	{
		assert(0);
	}
	if (!stroka)
	{
		assert(0);
	}

    size_t i = 0;
    int x = 0;
	int flag = 0;
	while (*(stroka + i) != '\0')
    {
		if((x = putc (*(stroka + i), filestream)) == EOF)
		{
			assert(0);
		}
		if (x == '\n') 
		{
			flag = 1;
			break;
		}
        i++;
    }
	if (!flag) putc ('\n', filestream);
	return 0;
}

int str_write_all (const Line* string_buffer, struct Information* file_data)
{
	if (!string_buffer)
	{
		assert(0);
	}

	size_t i = 0;
	while ((*(string_buffer + i)).start_line != nullptr)
	{
		str_write_solo ((*(string_buffer + i)).start_line, file_data -> file_write);
		i++;
	}
	fprintf(file_data -> file_write, "\n\n--------------------------------------------------------------------------------------------------------------------------------------------------------"
						               "\n--------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	return 1;
}

int bubble_sort (void* sort_buffer, const size_t len, const size_t size_one, int (*comparator) (const void*, const void*)) 
{
	if (!sort_buffer)
	{
		assert(0);
	}

	int x = 0;
	for (size_t i = 0; i < (len - 1); i++)
	{
		for (size_t j = i+1; j < len; j++)
		{	
			x = comparator ((void*)((char*) sort_buffer + i * size_one), (void*)((char*) sort_buffer + j * size_one));
			if (x == 1) 
			{
				change_elements ((void*)((char*) sort_buffer + i * size_one), (void*)((char*) sort_buffer + j * size_one), size_one);
			}
		}
	}
	return 1;
}

int comparator_start (const void* str11, const void* str22)
{
	if (!str11 || !str22)
	{
		assert(0);
	}

	Line str1       = {0, nullptr};
	Line str2       = {0, nullptr};
	str1.start_line = ((const Line*) str11) -> start_line;
	str2.start_line = ((const Line*) str22) -> start_line;
	str1.len        = ((const Line*) str11) -> len;
	str2.len        = ((const Line*) str22) -> len;

	size_t i        = 0;
	size_t j        = 0;
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
				return -1;
			}
			else
			{
				i++;
				j++;
			}
		}
	}
	return 0;
}

int comparator_end (const void* str11, const void* str22)
{
	if (!str11 || !str22)
	{
		assert(0);
	}
	
	Line str1       = {NULL, nullptr};
	Line str2       = {NULL, nullptr};
	str1.start_line = ((const Line*) str11) -> start_line;
	str2.start_line = ((const Line*) str22) -> start_line;
	str1.len        = ((const Line*) str11) -> len;
	str2.len        = ((const Line*) str22) -> len;
	
	size_t i        = str1.len;
	size_t j        = str2.len;
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
			else if (tolower (*(str1.start_line + i)) < tolower (*(str2.start_line + j)))
			{
				return -1;
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

int str_check (const char* stroka)
{
	if (!stroka)
	{
		assert(0);
	}
	
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

int change_elements (void* elem1, void* elem2, const size_t size_one)
{
	if (!elem1 || !elem2)
	{
		assert(0);
	}

	void* ptr = nullptr;
	ptr  = (void*) calloc (1, size_one);
	memcpy (ptr,   elem2, size_one);
	memcpy (elem2, elem1, size_one);
	memcpy (elem1, ptr,   size_one);
	free (ptr);
	return 1;
}