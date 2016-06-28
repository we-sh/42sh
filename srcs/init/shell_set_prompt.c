#include "shell.h"

/*
** TODO: Check for leaks and strjoin returns values.
*/

static int	s_fill_prompt(char **str, char *buf, char *home)
{
	if (buf && (ft_strncmp(buf, home, ft_strlen(home) - 1) == 0))
	{
		if ((*str = ft_strjoin3_safe("~", buf + ft_strlen(home),
			"$> ")) == NULL)
			return (ST_MALLOC);
	}
	else if (buf)
	{
		if ((*str = ft_strjoin(buf, "$> ")) == NULL)
			return (ST_MALLOC);
	}
	else
	{
		if ((*str = ft_strdup("$> ")) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

char		*shell_set_prompt(char **env)
{
	char	*str;
	char	*buf;
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	buf = getcwd(NULL, 0);
	home = env_get_home(env);
	if ((s_fill_prompt(&str, buf, home)) == ST_MALLOC)
	{
		free(str);
		return (NULL);
	}
	if ((conf_check_color_mode(env)) == ST_OK)
	{
		tmp = ft_strjoin3_safe(ANSI_COLOR_LIGHT_BLUE,
				str, ANSI_COLOR_RESET);
		free(str);
		str = tmp;
	}
	free(buf);
	return (str);
}
