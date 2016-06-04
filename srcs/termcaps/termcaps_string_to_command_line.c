#include "shell.h"

/*
** Add a string to the current command line
*/

int		termcaps_string_to_command_line(const size_t input_buffer_size,
										const char *input_buffer,
										t_list_head *command_line)
{
	size_t			input_buffer_index;
	size_t			character_bytes_count;
	size_t			character_missing_bytes_count;

	input_buffer_index = 0;
	while (input_buffer_index < input_buffer_size)
	{
		character_bytes_count =
			termcaps_get_character_bytes_count(input_buffer_size - input_buffer_index,
												input_buffer + input_buffer_index,
												&character_missing_bytes_count);
		if (character_bytes_count == 0 || character_missing_bytes_count > 0)
		{
			log_error("get_character_bytes_count() failed character bytes_count %zu missing_bytes_count %zu", character_bytes_count, character_missing_bytes_count);
			return (0);
		}
		if (!termcaps_character_to_command_line(character_bytes_count,
			input_buffer + input_buffer_index, command_line))
		{
			log_error("minishell__character_to_command_line() failed");
			return (0);
		}
		input_buffer_index += character_bytes_count;
	}
	return (1);
}
