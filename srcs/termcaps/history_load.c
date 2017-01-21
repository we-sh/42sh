#include "shell.h"
#include <sys/stat.h>

static int	s_stupidgetnextline(t_list_head *history, size_t *from,
								char *line, size_t offset)
{
	char	*pt;

	pt = line;
	while ((pt = ft_strchr(pt, '\t')))
	{
		*pt = ' ';
		pt++;
	}
	if (offset >= *from && ft_strlen(line) > 0)
	{
		if (!history_add(line, history))
		{
			free(line);
			return (0);
		}
	}
	free(line);
	return (1);
}

static int	read_history(int fd, t_list_head *history, size_t *from)
{
	char	*line;
	size_t	offset;

	offset = 0;
	while (get_next_line(fd, &line))
	{
		if (!s_stupidgetnextline(history, from, line, offset))
			return (0);
		offset++;
	}
	*from = offset;
	return (1);
}

int			file_exists(char *filename)
{
	struct stat	st;

	if (stat(filename, &st))
	{
		if (errno == ENOENT)
			return (0);
	}
	return (1);
}

int			history_load(char **envp, t_list_head *history, size_t *from)
{
	char	filename[255];
	int		fd;

	if (!history_get_filename(envp, sizeof(filename), filename))
		return (1);
	if (!file_exists(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ST_OPEN);
	if (!read_history(fd, history, from))
	{
		close(fd);
		return (ST_HISTORY_FILE_TOO_BIG);
	}
	close(fd);
	return (1);
}
