#include "shell.h"

/*
** TODO: Check for leaks and strjoin returns values.
*/

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
	if ((ft_strncmp(buf, home, ft_strlen(home) - 1) == 0))
	{
		str = ft_strjoin3_safe("~", buf + ft_strlen(home), "$> ");
		log_warn("%s", str);
	}
	else
		str = ft_strjoin(buf, "$> ");
	if ((conf_check_color_mode(env)) == ST_OK)
	{
		tmp = ft_strjoin3_safe(ANSI_COLOR_LIGHT_BLUE, str, ANSI_COLOR_RESET);
		free(str);
		str = tmp;
	}
	free(buf);
	return (str);
}
