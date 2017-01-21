#include "shell.h"
#include "get_next_line.h"
#include "i18n.h"

static int	s_conf_check_color(char *content)
{
	char	*mode;

	mode = content + 6;
	if (mode && *mode && ft_strncmp(mode, "on", 2) == 0)
	{
		shell_color_mode(1);
		return (ST_OK);
	}
	else if (mode && *mode && ft_strncmp(mode, "off", 2) == 0)
	{
		shell_color_mode(0);
		return (ST_OK);
	}
	return (-1);
}

static int	s_conf_check_lang(char *content)
{
	char	*mode;

	mode = content + 5;
	if (mode && *mode && ft_strncmp(mode, "fr", 2) == 0)
	{
		shell_language(LANG_FR);
		return (ST_OK);
	}
	else if (mode && *mode && ft_strncmp(mode, "en", 2) == 0)
	{
		shell_language(LANG_EN);
		return (ST_OK);
	}
	return (-1);
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
	fd = open(path, O_RDONLY);
	free(path);
	if (!(content = NULL) && fd == -1)
		return (ST_OK);
	while ((get_next_line(fd, &content)) == 1)
	{
		if (ft_strncmp(content, "color=", 6) == 0)
			s_conf_check_color(content);
		else if (ft_strncmp(content, "lang=", 5) == 0)
			s_conf_check_lang(content);
		free(content);
		content = NULL;
	}
	free(content);
	close(fd);
	return (-1);
}
