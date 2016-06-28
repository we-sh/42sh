#include "shell.h"

int			token_parse_utils_heredoc(t_sh *sh, int *fd, const char *trigger)
{
	t_termcaps_context	termcaps_context;
	char				*buffer;
	int					pipefd[2];
	int					ret;

	ret = ST_OK;
	if (pipe(pipefd) != 0)
		return (ST_PIPE);
	if (termcaps_initialize(sh, "heredoc> ", &termcaps_context) != 1)
		return (ST_TERMCAPS_INIT);
	termcaps_context.option = OPTION_HEREDOC;
	while (1)
	{
		buffer = termcaps_read_input(&termcaps_context);
		if (buffer == NULL)
			break ;
		if (!ft_strcmp("^C\n", buffer))
		{
			close(pipefd[0]);
			ret = ST_PARSER; //TEMP
			break ;
		}
		if (!ft_strcmp(buffer, trigger))
			break ;
		ft_putendl_fd(buffer, pipefd[1]);
		free(buffer);
	}
	free(buffer);
	termcaps_finalize(&termcaps_context);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (ret);
}
