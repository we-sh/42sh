#include "shell.h"

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
*/

int	parse(char const *input)
{
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
		job_launch(&j);
		/* TODO: free array */
	}
	return (ST_OK);
}
