#include "shell.h"

/*
** For now input shall be well espaced
** Split -> fill proc and job -> launch job
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
		j.stdin = STDIN_FILENO;
		j.stdout = STDOUT_FILENO;
		j.stderr = STDERR_FILENO;
		job_launch(&j);
		/* TODO: free array */
	}
	return (ST_OK);
}
