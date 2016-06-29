#include "shell.h"

/*
** Add a string to the current command line
*/

int		termcaps_string_to_command_line(const size_t input_buff_size,
										const char *input_buffer,
										t_list_head *command_line)
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
		if (!termcaps_character_to_command_line(char_b_count,
			input_buffer + input_buffer_index, command_line))
		{
			log_error("minishell__character_to_command_line() failed");
			return (0);
		}
		input_buffer_index += char_b_count;
	}
	return (1);
}
