#include "shell.h"

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
		{
			if (ft_strncmp(content+6, "on", 2) == 0)
			{
				log_success("COLOR %s", content);
				free(content);
				close(fd);
				return (ST_OK);
			}
			else
			{
				log_success("PAS  COLOR %s", content);
				free(content);
				close(fd);
				return (-1);
			}
		}
	}
	free(content);
	close(fd);
	return (ST_OK);
}