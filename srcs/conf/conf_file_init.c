#include "shell.h"

int			conf_file_init(char **env)
{
	int		fd;
	char	*path;
	char	*home;

	if ((home = env_get_home(env)) == NULL)
		return (ST_OK);
	if ((path = ft_strjoin3(home, "/", CONFIGURATION_FILE)) == NULL)
		return (ST_MALLOC);
	if (access(path, F_OK) == -1)
	{
		if ((fd = open(path, O_CREAT | O_WRONLY, 0644)) == -1)
		{
			free(path);
			log_error("open() failed");
			return (ST_OK);
		}
		write(fd, "color=on", 8);
		close(fd);
	}
	free(path);
	return (ST_OK);
}
