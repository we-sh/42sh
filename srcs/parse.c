#include "shell.h"

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
** WARNING: ft_strsplit return array even if input length == 0
*/

int	parse(char const *input)
{
	int		ret;
	t_job	j;
	t_proc	p;
	char	*cleaned;
	char	**array;

	cleaned = ft_strser(input);
	if (ft_strlen(cleaned) > 0 && (array = ft_strsplit(cleaned, ' ')) != NULL)
	{
		p.next = NULL;
		p.argv = array;
		p.pid = 0;
		p.completed = 0;
		p.stopped = 0;
		p.stdin = STDIN_FILENO;
		p.stdout = STDOUT_FILENO;
		p.stderr = STDERR_FILENO;
		p.exit_status = 0;
		j.next = NULL;
		j.proc = &p;
		j.command = (char *)input;
		j.foreground = 1;
		j.stdin = STDIN_FILENO;
		j.stdout = STDOUT_FILENO;
		j.stderr = STDERR_FILENO;
		j.pgid = 0;
		j.notified = 0;

		// temporary disguting:
		g_current_jobs = &j;

		if ((ret = job_launch(&j)) != ST_OK)
			log_fatal("job launch error: %s\n", i18n_translate(ret));
		/* TODO: free array */
	}
	ft_strdel(&cleaned);
	return (ST_OK);
}
