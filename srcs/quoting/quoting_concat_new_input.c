#include "shell.h"

static int				s_join_tmp(t_termcaps_context *chld,
										char *buff_quote,
										char **cmd,
										char **tmp)
{
	int ret;

	ret = 0;
	if (ft_strcmp(buff_quote, "^C\n") == 0)
	{
		chld->state = STATE_REGULAR;
		ret = -1;
		if ((*cmd = ft_strjoin(*tmp,"\n")) == NULL)
			ret = ST_MALLOC;
	}
	else if ((*cmd = ft_strjoin(*tmp, buff_quote)) == NULL)
		ret = ST_MALLOC;
	return (ret);	
}

int				concat_new_input(char **cmd,
									t_termcaps_context *chld,
									char **tmp)
{
	char				*buff_quote;
	int ret;

	buff_quote = NULL;
	buff_quote = termcaps_read_input(chld);
	ret = s_join_tmp(chld, buff_quote, cmd, tmp);
	free(*tmp);
	ft_memdel((void **)&buff_quote);
	return (ret);
}
