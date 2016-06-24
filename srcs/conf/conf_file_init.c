#include "shell.h"

int			conf_file_init(void)
{
	int		fd;

	if ((fd = open(".weshrc", O_CREAT | O_RDWR, 0644)) == -1)
	{
		log_error("open() failed");
		return (ST_OPEN);
	}
	write(fd, "color=on\n", 9);
	close(fd);
	return (ST_OK);
}