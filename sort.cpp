#include "head.h"

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

void str_write_all (char** string_buffer, struct Information* file_data)
{
	size_t i = 0;
	while (*(string_buffer + i) != nullptr)
	{
		str_write_solo (*(string_buffer + i), file_data -> file_write);
		i++;
	}
	fprintf(file_data -> file_write, "\n\n--------------------------------------------------------------------------------------------------------------------------------------------------------"
						"\n--------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void destructor (struct Information* file_data)
{
	//string_buffer
	char *symbol = file_data -> text_buffer;
	size_t p = 0;
	size_t amount = 1;
	*(file_data -> string_buffer) = file_data -> text_buffer;
	while (*(symbol + p) != '\0')
	{
		if ((*(symbol + p) == 10) && (*(symbol + p + 1) != '\0'))
		{
			*(file_data -> string_buffer + amount) = symbol + p + 1;
			amount++;
		}
		p++;
	}
	if (*(file_data -> string_buffer + amount) != NULL)
	{
		assert(0);
	}
	//sort1_buffer and sort2_buffer
	file_data -> good_strings = 0;
	size_t all = 0;
	while (*(file_data -> string_buffer + all) != nullptr)
	{
		if (str_check (*(file_data -> string_buffer + all)))
		{
			all++;
			continue;
		}
		(file_data -> good_strings)++;
		all++;
	}
	(file_data -> good_strings)++;
	if ((file_data -> sort1_buffer = (char**) calloc (file_data -> good_strings + 1, sizeof (char*))) == nullptr)
	{
		assert(0);
	}
	if ((file_data -> sort2_buffer = (char**) calloc (file_data -> good_strings + 1, sizeof (char*))) == nullptr)
	{
		assert(0);
	}
	size_t m = 0;
	for (size_t i = 0; i < file_data -> n_strings; i++)
	{	

		if (str_check (*(file_data -> string_buffer + i)))
		{
			continue;
		}
		*(file_data -> sort1_buffer + m) = *(file_data -> string_buffer + i);
		*(file_data -> sort2_buffer + m) = *(file_data -> string_buffer + i);
		m++;
	}
	bubble_sort (file_data -> sort1_buffer, file_data -> good_strings, comparator1);
	bubble_sort (file_data -> sort2_buffer, file_data -> good_strings, comparator2);

	str_write_all (file_data -> string_buffer, file_data);
    str_write_all (file_data -> sort1_buffer,  file_data);
    str_write_all (file_data -> sort2_buffer,  file_data);

	free(file_data -> text_buffer);
	free(file_data -> string_buffer);
	free(file_data -> sort1_buffer);
	free(file_data -> sort1_buffer);

	file_close(file_data -> file_write);
	file_close(file_data -> file_text);
}

void bubble_sort (char** array, size_t len, int (*comparator) (char*, char*))
{
	char* ptr = nullptr;
	for (size_t i = 0; i < (len - 2); i++)
	{
		for (size_t j = i+1; j < (len - 1); j++)
		{
			if (comparator (*(array + i), *(array + j))) 
			{
				ptr = *(array + j);
				*(array + j) = *(array + i);
				*(array + i) = ptr;
			}
		}
	}
}

int comparator1 (char* str1, char* str2)
{
	size_t i  = 0;
	size_t j  = 0;
	int flag1 = 0;
	int flag2 = 0;
	while ((*(str1 + i) != '\0') && (*(str1 + i) != '\n') && (*(str2 + j) != '\0') && (*(str2 + j) != '\n'))
	{
		if (((*(str1 + i) < 97) || (*(str1 + i) > 122)) && ((*(str1 + i) < 65) || (*(str1 + i) > 90)))
		{
			flag1 = 0;
			i++;
		}
		else
		{
			flag1 = 1;
		}
		if (((*(str2 + j) < 97) || (*(str2 + j) > 122)) && ((*(str2 + j) < 65) || (*(str2 + j) > 90)))
		{
			flag2 = 0;
			j++;
		}
		else
		{
			flag2 = 1;
		}
		if (flag1 && flag2)
		{
			if      (tolower (*(str1 + i)) > tolower (*(str2 + j)))
			{
				return 1;
			}
			else if (tolower (*(str1 + i)) < tolower (*(str2 + j)))
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

int comparator2 (char* str1, char* str2)
{
	size_t i = 0;
	int flag1 = 0;
	int flag2 = 0;
	while (*(str1+i) != '\n')
	{
		i++;
	}
	size_t j = 0;
	while (*(str2+j) != '\n')
	{
		j++;
	}
	while ((i != 0) && (j != 0))
	{
		if (((*(str1 + i) > 97) && (*(str1 + i) < 122)) || ((*(str1 + i) > 65) && (*(str1 + i) < 90)))
		{
			flag1 = 1;
		}
		else
		{
			flag1 = 0;
			i--;
		}
		if (((*(str2 + j) > 97) && (*(str2 + j) < 122)) || ((*(str2 + j) > 65) && (*(str2 + j) < 90)))
		{
			flag2 = 1;
		}
		else
		{
			flag2 = 0;
			j--;
		}
		if (flag1 && flag2)
		{
			if      (tolower (*(str1 + i)) > tolower (*(str2 + j)))
			{
				return 1;
			}
			else if (tolower (*(str1 + i)) < tolower (*(str2 + j)))
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
	size_t leng = 0;
	size_t counter_letters = 0;
	while ((*(stroka + leng) != '\0') && (*(stroka + leng) != '\n'))
	{
		if (((*(stroka + leng) > 97) && (*(stroka + leng) < 122)) || ((*(stroka + leng) > 65) && (*(stroka + leng) < 90)))
		{
			counter_letters++;
		}
		leng++;
	}
	if (counter_letters == 0)
	{
		return 1;
	}
	return 0;
}

