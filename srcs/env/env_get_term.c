#include "shell.h"

char				*env_get_term(char **envp)
{
	char			*tmp;
	char			*bd;

	bd = NULL;
	if ((tmp = env_get(envp, "TERM")) == NULL)
	{
		if (!tgetent(bd, "xterm"))
		{
			return (NULL);
		}
		else
			tmp = "xterm";
	}
	return (tmp);
}
