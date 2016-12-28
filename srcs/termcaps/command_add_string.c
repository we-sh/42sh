#include "shell.h"

/*
** Add a string to the current command line
*/

int		command_add_string(const size_t input_buff_size,
										const char *input_buffer,
										t_list_head *command)
{
	size_t			input_buffer_index;
	size_t			char_b_count;
	size_t			char_miss_bcnt;

	input_buffer_index = 0;
	while (input_buffer_index < input_buff_size)
	{
		char_b_count =
		termcaps_get_character_bytes_count(input_buff_size - input_buffer_index,
											input_buffer + input_buffer_index,
											&char_miss_bcnt);
		if (char_b_count == 0 || char_miss_bcnt > 0)
		{
			log_error("get_char_b_count() error", char_b_count, char_miss_bcnt);
			return (0);
		}
		if (!command_add(char_b_count,
			input_buffer + input_buffer_index, command))
		{
			log_error("minishell__character_to_command() failed");
			return (0);
		}
		input_buffer_index += char_b_count;
	}
	return (1);
}
