#include "head.h"

void destructor (struct Information* file_data)
{
	free(file_data -> text_buffer);
	free(file_data -> string_buffer);
	free(file_data -> sort1_buffer);
	free(file_data -> sort2_buffer); //ub wsl

	file_close(file_data -> file_write);
	file_close(file_data -> file_text);
}


