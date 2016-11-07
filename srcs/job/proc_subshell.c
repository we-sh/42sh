#include "shell.h"

int				s_launch(t_sh *sh, t_job *j, t_proc *p)
{
	int			ret;

	sh->is_interactive = 0;
	job_list_clean_except_job(j);
	if ((ret = loop_job_launcher(sh, p->argv[0], 1)) != ST_OK)
		return (ret);
	return (ST_OK);
}

void			proc_subshell(t_sh *sh, t_job *j, t_proc *p)
{
	int			ret;

	if ((ret = s_launch(sh, j, p)) != ST_OK)
	{
		display_status(ret, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	exit(sh->last_exit_status);
}
