#include "shell.h"

int			conf_check_color_mode(void)
{
	int		fd;
	char	*content;

	if ((fd = open(".weshrc", O_RDONLY)) == -1)
	{
		log_error("open() failed");
		return (ST_OPEN);
	}
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
			else if (ft_strncmp(content+6, "off", 2) == 0)
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