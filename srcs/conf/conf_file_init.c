#include "shell.h"

int			conf_file_init(char **env)
{
	int		fd;
	char	*path;

	path = ft_strjoin(env_get_home(env), "/.weshrc");
	if ((fd = open(path, O_CREAT | O_RDWR, 0644)) == -1)
	{
		free(path);
		log_error("open() failed");
		return (ST_OPEN);
	}
	write(fd, "color=on\n", 9);
	close(fd);
	free(path);
	return (ST_OK);
}