#include "shell.h"

/*
** TODO: Check for leaks and strjoin returns values.
*/

char		*shell_set_prompt(char **env)
{
	char	*str;
	char	*buf;
	char	*home;
	char	*tmp;

	if ((buf = getcwd(NULL, 0)) == NULL)
		return (NULL);
	if ((home = env_get_home(env)) == NULL)
		return (NULL);
	if ((ft_strncmp(buf, home, ft_strlen(home) - 1) == 0))
		str = ft_strjoin3_safe("~", buf + ft_strlen(home), "$> ");
	else
		str = ft_strjoin(buf, "$> ");
	if (!str)
		return (NULL);
	if ((conf_check_color_mode(env)) == ST_OK)
	{
		tmp = ft_strjoin3_safe(ANSI_COLOR_LIGHT_BLUE, str, ANSI_COLOR_RESET);
		if (!tmp)
			return (NULL);
		free(str);
		str = tmp;
	}
	free(buf);
	return (str);
}
