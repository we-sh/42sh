#include "shell.h"

int		termcaps_write(int fd, char *buffer, size_t buffer_size)
{
	int		nb_write_total;
	int		nb_write;

	nb_write_total = 0;
	while ((size_t)nb_write_total != buffer_size)
	{
		nb_write = write(fd, buffer + nb_write_total,
						buffer_size - nb_write_total);
		if (nb_write < 0)
		{
			return (0);
		}
		nb_write_total += nb_write;
	}
	return (1);
}
