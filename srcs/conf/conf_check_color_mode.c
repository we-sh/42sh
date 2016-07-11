#include "shell.h"

static int	s_conf_check_mode(char *content, int fd)
{
	int		ret;
	char	*mode;

	ret = -1;
	if (content)
	{
		mode = content + 6;
		if (mode && *mode && ft_strncmp(mode, "on", 2) == 0)
			ret = ST_OK;
		close(fd);
		free(content);
	}
	return (ret);
}

int			conf_check_color_mode(char **env)
{
	int		fd;
	char	*content;
	char	*color;
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
	content = NULL;
	color = NULL;
	while ((get_next_line(fd, &content)) == 1)
	{
		if (ft_strncmp(content, "color=", 6) == 0)
			color = ft_strdup(content);
		free(content);
	}
	return (s_conf_check_mode(color, fd));
}
