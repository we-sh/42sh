#include "shell.h"
#include "get_next_line.h"

static int	s_conf_check_mode(char *content, int fd)
{
	char	*mode;

	mode = content + 6;
	if (mode && *mode && ft_strncmp(mode, "on", 2) == 0)
	{
		free(content);
		close(fd);
		return (ST_OK);
	}
	else
	{
		free(content);
		close(fd);
		return (-1);
	}
}

int			conf_check_color_mode(char **env)
{
	int		fd;
	char	*content;
	char	*path;

	env = NULL;
	if ((content = env_get_home(env)) == NULL)
		return (ST_OK);
	if ((path = ft_strjoin3(content, "/", CONFIGURATION_FILE)) == NULL)
		return (ST_MALLOC);
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		free(path);
		return (ST_OK);
	}
	free(path);
	while ((get_next_line(fd, &content)) == 1)
	{
		if (ft_strncmp(content, "color=", 6) == 0)
			return (s_conf_check_mode(content, fd));
	}
	free(content);
	close(fd);
	return (-1);
}
