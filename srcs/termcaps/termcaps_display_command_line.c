#include "shell.h"
#include <sys/ioctl.h>
#include <termios.h>

/*
** Display the command line
*/

#define ENDL_SIZE	(sizeof("\n") - 1)
#define ENDL				"\n"

int			termcaps_display_command_line(const int fd, const t_list_head *command_line)
{
	size_t	buffer_size_max;
	size_t	buffer_size;
	char	*buffer;
	int		nb_write_total;
	int		nb_write;

	buffer_size_max = command_line->size * CHARACTER_SIZE_MAX;
	buffer = malloc(buffer_size_max);
	if (!buffer)
	{
		log_error("malloc() failed command_line->size %zu", buffer_size_max);
		return (0);
	}
	if (!list_head__command_line_to_buffer(command_line,
											buffer_size_max - ENDL_SIZE,
											&buffer_size,
											buffer))
	{
		log_error("list_head__command_line_to_buffer()");
		free(buffer);
		return (0);
	}
	if (buffer_size % caps__win(WIN_COLUMNS) == 0)
	{
		log_fatal("WHATTTTTTT ???");
		ft_memcpy(buffer + buffer_size, ENDL, ENDL_SIZE);
		buffer_size += ENDL_SIZE;
	}

	//TEMP ?
	//log_debug("writing %.*s", (int)buffer_size, buffer);

	nb_write_total = 0;
	while ((size_t)nb_write_total != buffer_size)
	{
		nb_write = write(fd, buffer + nb_write_total, buffer_size - nb_write_total);
		if (nb_write < 0)
		{
			log_fatal("write() failed");
			return (0);
		}
		nb_write_total += nb_write;
	}

	free(buffer);
	return (1);
}
