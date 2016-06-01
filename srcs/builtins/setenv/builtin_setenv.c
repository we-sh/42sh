#include "shell.h"

# define HAVE_ARGV 2

static int s_concat_variable(char **str, char *key, char *value)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(key, "="); //checker les retour de strdup MALLOC
	if (!value)
	{
		*str = ft_strdup(tmp);
		free(tmp);	
	}
	else if (value)
	{
		//ft_putendl_fd(value, 1);//debug
		tmp2 = ft_strjoin(tmp, value);//checker les retour de strdup MALLOC
		free(tmp);
		*str = ft_strdup(tmp2);
		free(tmp2);
	}
	return (ST_OK);
}

static char **s_env_set_new_variable(t_sh **sh, char *variable, char *value)
{
	char **tmp;
	int i;
	int size;

	i = 0;
	size = 0;


		ft_putendl_fd("IN inside env_set_new_variable", 1);//debug
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);


	while ((*sh)->envp[size])
		size++;
	tmp = (char **)malloc(sizeof(char *) * size + 2);


		ft_putendl_fd("IN inside env_set_new_variable1", 1);//debug
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	while ((*sh)->envp[i] != NULL)
	{
			// ft_putnbr_fd(i, 1); // debug
			// ft_putendl_fd((*sh)->envp[i], 1);//debug
			// caps__print_cap(CAPS__CARRIAGE_RETURN, 0);


		tmp[i] = ft_strdup((*sh)->envp[i]);
//		free((*sh)->envp[i]);
		i++;
	}

	s_concat_variable(&(tmp[i]), variable, value);
	i++;
	//ft_memdel_tab((void ***)&(*sh)->envp);
	tmp[i] = NULL;


		ft_putendl_fd("IN inside env_set_new_variable2", 1);//debug
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		ft_putendl_fd(" OUT inside env_set_new_variable", 1);//debug	
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	return (tmp);
}

static int s_env_index_value(t_sh *sh, char *variable)
{
	int 	i;
	int 	size;

	i = 0;
	size = ft_strlen(variable);
//	ft_putendl_fd("env_index_value", 1);//debug
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], variable, size) == 0)
		{
			if (!sh->envp[i][size])
				return (-1);
			else if (sh->envp[i][size] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

static int s_env_set_variable_and_value(t_sh **sh, t_proc *p)
{
	int i;
	int ret;
	char **tmp;

	ret = 0;
	i = 0;
			// ft_putendl_fd("set_variable_and_value", 1);//debug
	if ((ret = s_env_index_value(*sh, p->argv[1])) == -1)
	{
			ft_putendl_fd("set_variable_and_value est  - 1", 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
			ft_putendl_fd(" inside variable_and_value", 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);


		tmp = s_env_set_new_variable(sh, p->argv[1], p->argv[2]);
		//ft_memdel_tab((void ***)&(*sh)->envp);

			ft_putendl_fd(" inside variable_and_value 2", 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		(*sh)->envp = tmp;
			ft_putendl_fd(" inside variable_and_value 3", 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		while ((*sh)->envp[i])
		{
			ft_putendl_fd((*sh)->envp[i], 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
			i++;
		}
			ft_putendl_fd(" inside variable_and_value 4", 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	}
	else
	{
			ft_putstr_fd("set_variable_and_value est ", 1);//debug
			ft_putnbr_fd(ret, 1);//debug
			ft_putstr_fd("\n", 1);//debug
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);



		if (!p->argv[2])
			s_concat_variable(&(*sh)->envp[ret], p->argv[1], NULL);
		else if (p->argv[2])
			s_concat_variable(&(*sh)->envp[ret], p->argv[1], p->argv[2]);
	}


		ft_putendl_fd(" OUT variable_and_value", 1);//debug	
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);


	return (ST_OK);
}

static int s_check_if_alphanum(t_proc *p)
{
	int 	i;

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

static int s_check_if_start_with_letter(t_proc *p)
{
	if (p->argv[1])
	{
		if (ft_isalpha(p->argv[1][0]) == 0 && p->argv[1][0] != '_')
			return (ST_BLTIN_SETENV_FIRST_CHAR);
	}
	return (ST_OK);	
}

static int	s_argv_is_valid(t_proc *p)
{
	if (s_check_if_start_with_letter(p) == ST_BLTIN_SETENV_FIRST_CHAR)
		return (ST_BLTIN_SETENV_FIRST_CHAR);
	if (s_check_if_alphanum(p) == ST_BLTIN_SETENV_ALPHA_NUM)
		return (ST_BLTIN_SETENV_ALPHA_NUM);
	return (ST_OK);
}

static int	s_before(t_proc *p)
{
	int		ret;

	ret = 0;
	if (p->bltin_status == ST_OK)
	{
		if (p->argc > 1)
		{
			if (p->argc > 3)
				p->bltin_status = ST_BLTIN_SETENV_TMANY_ARGV;
			else if (((ret  = s_argv_is_valid(p)) != ST_OK))
				p->bltin_status = ret;
			else
				p->bltin_status = HAVE_ARGV;
		}
	}
	if (p->bltin_status == HAVE_ARGV)
	{
		ft_putendl_fd("Before no error", 1);//debug
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);//debug
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p, t_sh *sh)
{
	int		i;

	i = 0;
	if (p->bltin_status == ST_OK)
	{
		while (sh->envp[i])
		{
			ft_putendl_fd(sh->envp[i], STDOUT_FILENO);
			i++;
		}	
	}
	else if (p->bltin_status != ST_OK && p->bltin_status != HAVE_ARGV)
	{
		// todo use `log_status()` instead
		ft_putendl_fd(i18n_translate(p->bltin_status), STDERR_FILENO);
		if (p->bltin_status == ST_EINVAL)
		{
			ft_putstr_fd(i18n_translate(ST_USAGE), STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(builtin->usage, STDERR_FILENO);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh **sh, t_proc *p)
{

	if (p->bltin_status == HAVE_ARGV)
		s_env_set_variable_and_value(sh, p);
	p->bltin_status = ST_OK;
	return (ST_OK);
}

int			builtin_setenv(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p, sh));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}
