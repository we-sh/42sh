#include "shell.h"

void	wrap_histfile(t_sh *sh, int opt, char *filename,
						void (*fun)(t_sh *, int))
{
	char	*histfile;

	histfile = NULL;
	if (filename != NULL)
	{
		histfile = env_get(sh->envp, "HISTFILE");
		if (histfile != NULL)
			histfile = ft_strdup(histfile);
		env_set(&sh->envp, "HISTFILE", filename);
	}
	fun(sh, opt);
	if (filename != NULL)
	{
		if (histfile != NULL)
			env_set(&sh->envp, "HISTFILE", histfile);
	}
}
