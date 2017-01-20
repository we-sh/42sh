#include "shell.h"

static int		s_history_write(t_list_head *history, int fd, int append)
{
	t_list			*pos;
	t_node_history	*node;

	pos = &history->list;
	while ((pos = pos->next) && pos != &history->list)
	{
		node = CONTAINER_OF(pos, t_node_history, list);
		if (append && !node->is_modified)
			continue ;
		if (!termcaps_write(fd, node->command.bytes, node->command.size) ||
			!termcaps_write(fd, "\n", sizeof("\n") - 1))
		{
			return (0);
		}
	}
	return (1);
}

int				history_write(char **envp, t_list_head *history, int append)
{
	char	filename[255];
	int		fd;
	int		flags;

	if (!history_get_filename(envp, sizeof(filename), filename))
	{
		return (0);
	}
	flags = append ? O_CREAT | O_WRONLY :
					O_CREAT | O_WRONLY | O_TRUNC;
	fd = open(filename, flags, 0666);
	if (fd == -1)
	{
		return (0);
	}
	if (append)
		lseek(fd, 0, SEEK_END);
	s_history_write(history, fd, append);
	close(fd);
	return (1);
}
