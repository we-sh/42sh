#include "shell.h"

static int	s_check_if_alphanum(char const *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if ((ft_isalnum(arg[i]) == 1)
			|| (ft_isalpha(arg[i]) == 1)
			|| (arg[i] == '_'))
			i++;
		else
			return (ST_BLTIN_SETENV_ALPHA_NUM);
	}
	return (ST_OK);
}

static	int	s_check_if_start_with_letter(char const *arg)
{
	if (arg)
	{
		if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
			return (ST_BLTIN_SETENV_FIRST_CHAR);
	}
	return (ST_OK);
}

int			setenv_argv_is_valid(char const *arg)
{
	if (s_check_if_start_with_letter(arg) == ST_BLTIN_SETENV_FIRST_CHAR)
		return (ST_BLTIN_SETENV_FIRST_CHAR);
	if (s_check_if_alphanum(arg) == ST_BLTIN_SETENV_ALPHA_NUM)
		return (ST_BLTIN_SETENV_ALPHA_NUM);
	return (ST_OK);
}
