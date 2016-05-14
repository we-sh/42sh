#include "shell.h"

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
*/

int	parse(char const *input)
{
	int		ret;
	t_job	j;
	t_proc	p;
	char	**array;

	if ((array = ft_strsplit(input, ' ')))
	{
		p.next = NULL;
		p.argv = array;
		j.next = NULL;
		j.proc = &p;
		j.command = (char *)input;
		j.foreground = 1;
		j.stdin = STDIN_FILENO;
		j.stdout = STDOUT_FILENO;
		j.stderr = STDERR_FILENO;
		if ((ret = job_launch(&j)) != ST_OK)
			log_fatal("job launch error: %s\n", i18n_translate(ret));
		/* TODO: free array */
	}
	return (ST_OK);
}
