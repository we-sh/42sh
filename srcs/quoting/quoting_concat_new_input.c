#include "shell.h"

static int				s_realloc_buff(char **buff_quote)
{
	char				*tmpbuff;

	if ((tmpbuff = ft_strdup(*buff_quote + 1)) == NULL)
		return (ST_MALLOC);
	free(*buff_quote);
	if ((*buff_quote = ft_strdup(tmpbuff)) == NULL)
		return (ST_MALLOC);
	free(tmpbuff);	
	return (ST_OK);
}

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
									int tokenid,
									char **tmp)
{
	char				*buff_quote;
	int ret;

	buff_quote = NULL;
	if (tokenid == TC_BACKSLASH)
		termcaps_string_to_command_line(chld->fd, "\0",
			&chld->command_line);
	buff_quote = termcaps_read_input(chld);
	if (tokenid == TC_BACKSLASH)
	{
		if ((s_realloc_buff(&buff_quote)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	ret = s_join_tmp(chld, buff_quote, cmd, tmp);
	free(*tmp);
	ft_memdel((void **)&buff_quote);
	return (ret);
}
