#include "shell.h"

/*
** Tilde `~` must be the first expansion to perform.
*/

char		*expand_tilde(t_proc *p, char *input)
{
	char	*tmp;
	char	*output;

	log_debug("expanding tilde");
	output = input;
	if (input[0] == '~')
	{
		tmp = env_get_home(p->envp);
		if (tmp)
		{
			output = ft_strjoin(tmp, input + 1);
			ft_memdel((void **)&input);
		}
	}
	return (output);
}
