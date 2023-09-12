#include "head.h"

int str_compare1 (char* str1, char* str2)
{
	size_t i = 0;
	size_t j = 0;
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
			if (tolower (*(str1 + i)) > tolower (*(str2 + j)))
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

char** str_sort1_buff (char** str_orig_buff)
{
	size_t n_strok = 0;
	size_t all = 0;
	while (*(str_orig_buff + all) != nullptr)
	{
		if (str_check (*(str_orig_buff + all)))
		{
			all++;
			continue;
		}
		n_strok++;
		all++;
	}
	n_strok++;
	char** str_sort1_buffer = nullptr;

	if ((str_sort1_buffer = (char**) calloc (n_strok + 1, sizeof(char*))) == nullptr)
	{
		assert(0);
	}

	size_t m = 0;
	for (size_t i = 0; i < all; i++)
	{
		if (str_check (*(str_orig_buff + i)))
		{
			continue;
		}

		*(str_sort1_buffer + m) = *(str_orig_buff + i);
		m++;
	}

	bubble_sort1 (str_sort1_buffer, n_strok);

	return str_sort1_buffer;
}

void bubble_sort1 (char** array, size_t len)
{
	char* ptr = nullptr;
	for (size_t i = 0; i < len - 2; i++)
	{
		for (size_t j = i+1; j < len - 1; j++)
		{
			if (str_compare1 (*(array + i), *(array + j))) 
			{
				ptr = *(array + j);
				*(array + j) = *(array + i);
				*(array + i) = ptr;
			}
		}
	}
}

char** str_sort2_buff (char** str_orig_buff)
{
	size_t n_strok = 0;
	size_t all = 0;
	while (*(str_orig_buff + all) != nullptr)
	{
		if (str_check (*(str_orig_buff + all)))
		{
			all++;
			continue;
		}
		n_strok++;
		all++;
	}
	n_strok++;

	char** str_sort2_buffer = nullptr;
	if ((str_sort2_buffer = (char**) calloc (n_strok + 1, sizeof(char*))) == nullptr)
	{
		assert(0);
	}

	size_t m = 0;
	for (size_t i = 0; i < all; i++)
	{
		if (str_check (*(str_orig_buff + i)))
		{
			continue;
		}
		*(str_sort2_buffer + m) = *(str_orig_buff + i);
		m++;
	}

	bubble_sort2 (str_sort2_buffer, n_strok);

	return str_sort2_buffer;
}

void bubble_sort2 (char** array, size_t len)
{
	char* ptr = nullptr;
	for (size_t i = 0; i < len - 2; i++)
	{
		for (size_t j = i+1; j < len - 1; j++)
		{
			if (str_compare2 (*(array + i), *(array + j))) 
			{
				ptr = *(array + j);
				*(array + j) = *(array + i);
				*(array + i) = ptr;
			}
		}
	}
}


int str_compare2 (char* str1, char* str2)
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
			if (tolower (*(str1 + i)) > tolower (*(str2 + j)))
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