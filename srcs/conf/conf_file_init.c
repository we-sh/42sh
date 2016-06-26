#include "shell.h"

int			conf_file_init(char **env)
{
	int		fd;
	char	*path;

	path = ft_strjoin(env_get_home(env), "/.weshrc");
	if (access(path, F_OK) == -1)
	{
		if ((fd = open(path, O_CREAT | O_RDWR, 0644)) == -1)
		{
			free(path);
			log_error("open() failed");
			return (ST_OPEN);
		}
		write(fd, "color=on", 8);
		close(fd);
	}
	free(path);
	return (ST_OK);
}
