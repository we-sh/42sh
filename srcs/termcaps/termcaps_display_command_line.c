#include "shell.h"

/*
** Display the command line
*/

int			termcaps_display_command_line(const t_list_head *command_line)
{
	size_t	buffer_size_max;
	size_t	buffer_size;
	char	*buffer;

	buffer_size_max = command_line->size * CHARACTER_SIZE_MAX;
	buffer = malloc(buffer_size_max);
	if (!buffer)
	{
		log_error("malloc() failed command_line->size %zu", buffer_size_max);
		return (0);
	}
	if (!list_head__command_line_to_buffer(command_line,
											buffer_size_max,
											&buffer_size,
											buffer))
	{
		log_error("list_head__command_line_to_buffer() %s", "");
		free(buffer);
		return (0);
	}
	write(1, buffer, buffer_size);
	if (buffer_size % caps__win(WIN_COLUMNS) == 0)
	{
		caps__print_cap(CAPS__DOWN, 0);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	}
	free(buffer);
	return (1);
}
