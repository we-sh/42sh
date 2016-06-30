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

char		*shell_set_prompt(t_sh *sh)
{
	char	*str;
	char	*buf;
	int		i;
	char	*home;

	i = 0;
	buf = sh->pwd ? sh->pwd : getcwd(NULL, 0);
	if (!buf)
		return (NULL);
	if ((home = env_get_home(sh->envp)) == NULL)
		return (NULL);
	if ((s_fill_prompt(&str, buf, home)) == ST_MALLOC)
	{
		free(str);
		return (NULL);
	}
	if (!sh->pwd)
		free(buf);
	return (str);
}
