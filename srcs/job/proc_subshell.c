#include "shell.h"

int				s_launch(t_sh *sh, t_proc *p)
{
	int			ret;
	char		*shlvl_char;
	int			shlvl;

	if ((shlvl_char = env_get(sh->envp, "SHLVL")) != NULL)
		shlvl = ft_atoi(shlvl_char) + 1;
	else
		shlvl = 1;
	if ((shlvl_char = ft_itoa(shlvl)) == NULL)
		return (ST_MALLOC);
	if ((ret = env_set(&sh->envp, "SHLVL", shlvl_char)) != ST_OK)
		return (ret);
	free(shlvl_char);
	sh->is_interactive = 0;
	if ((ret = loop_job_launcher(sh, p->argv[0])) != ST_OK)
		return (ret);
	return (ST_OK);
}

void			proc_subshell(t_sh *sh, t_proc *p)
{
	int			ret;

	log_success("subshell: %s", p->argv[0]);
	if ((ret = s_launch(sh, p)) != ST_OK)
	{
		display_status(ret, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	exit(sh->last_exit_status);
}
