#include "shell.h"

void			proc_subshell(t_sh *sh, t_job *j, t_proc *p)
{
	int			ret;
	(void)j;

	log_success("subshell: %s", p->argv[0]);
	sh->is_interactive = 0;
	ret = loop_job_launcher(sh, p->argv[0]);

	log_fatal("TODO: exit subshell");
	exit(0);
}
