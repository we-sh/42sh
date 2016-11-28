#include "shell.h"

static int	read_history(int fd, t_list_head *history, size_t *from)
{
	char	*line;
	size_t	offset;

	offset = 0;
	while (get_next_line(fd, &line))
	{
		if (offset >= *from)
		{
			if (!history_add(line, history))
			{
				log_error("history_add failed line {%s}", line);
				free(line);
				return (0);
			}
		}
		free(line);
		offset++;
	}
	*from = offset;
	return (1);
}

int		file_exists(char *filename)
{
	struct stat	st;

	if (stat(filename, &st))
	{
		if (errno == ENOENT)
			return (0);
	}
	return (1);
}

int		history_load(char *filename, t_list_head *history, size_t *from)
{
	int		fd;

	if (!file_exists(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		log_error("open: %s failed errno %d", filename, errno);
		return (0);
	}
	if (!read_history(fd, history, from))
	{
		log_error("read_history %s failed", filename);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
