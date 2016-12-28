#include "shell.h"

void	append_history(t_list_head *history, t_proc *p)
{
	char	cmd[1024];
	int		i;

	cmd[0] = '\0';
	i = 1;
	while (i < p->argc)
	{
		ft_strlcat(cmd, p->argv[i], sizeof(cmd));
		ft_strlcat(cmd, " ", sizeof(cmd));
		i++;
	}
	history_add(cmd, history);
}
