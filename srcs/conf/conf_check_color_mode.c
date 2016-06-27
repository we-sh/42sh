#include "shell.h"

static int	s_conf_check_mode(char *content, int fd)
{
	char	*mode;

	mode = content + 6;
	if (mode && *mode && ft_strncmp(mode, "on", 2) == 0)
	{
		free(content);
		close(fd);
		log_success("color is activated.");
		return (ST_OK);
	}
	else
	{
		free(content);
		close(fd);
		log_success("color is not activated.");
		return (-1);
	}
}

int			conf_check_color_mode(char **env)
{
	int		fd;
	char	*content;
	char	*path;

	env = NULL;
	path = ft_strjoin(env_get_home(env), "/.weshrc");
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		free(path);
		log_error("open() failed");
		return (ST_OPEN);
	}
	free(path);
	while ((get_next_line(fd, &content)) == 1)
	{
		if (ft_strncmp(content, "color=", 6) == 0)
			return (s_conf_check_mode(content, fd));
	}
	log_warn("color behaviour is not specified.");
	free(content);
	close(fd);
	return (-1);
}
