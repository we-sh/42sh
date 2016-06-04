#include "shell.h"

static	int s_check_if_alphanum(t_proc *p)
{
	int		i;

	i = 0;
	while (p->argv[1][i])
	{
		if ((ft_isalnum(p->argv[1][i]) == 1)
			|| (ft_isalpha(p->argv[1][i]) == 1)
			|| (p->argv[1][i] == '_'))
			i++;
		else
			return (ST_BLTIN_SETENV_ALPHA_NUM);
	}
	return (ST_OK);
}

static	int	s_check_if_start_with_letter(t_proc *p)
{
	if (p->argv[1])
	{
		if (ft_isalpha(p->argv[1][0]) == 0 && p->argv[1][0] != '_')
			return (ST_BLTIN_SETENV_FIRST_CHAR);
	}
	return (ST_OK);
}

int			setenv_argv_is_valid(t_proc *p)
{
	if (s_check_if_start_with_letter(p) == ST_BLTIN_SETENV_FIRST_CHAR)
		return (ST_BLTIN_SETENV_FIRST_CHAR);
	if (s_check_if_alphanum(p) == ST_BLTIN_SETENV_ALPHA_NUM)
		return (ST_BLTIN_SETENV_ALPHA_NUM);
	return (ST_OK);
}
