/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	s_read_input(char const *trigger, int *ret,
				t_termcaps_context *termcaps_context, int *pipefd)
{
	char				*buffer;

	buffer = termcaps_read_input(termcaps_context);
	if (buffer == NULL)
		return (ST_BREAK);
	if (!ft_strcmp("^C\n", buffer))
	{
		close(pipefd[0]);
		*ret = ST_PARSER;
		free(buffer);
		return (ST_BREAK);
	}
	if (!ft_strcmp(buffer, trigger))
	{
		free(buffer);
		return (ST_BREAK);
	}
	ft_putendl_fd(buffer, pipefd[1]);
	free(buffer);
	return (ST_OK);
}

int			token_parse_utils_heredoc(t_sh *sh, int *fd, const char *trigger)
{
	t_termcaps_context	termcaps_context;
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
		if (s_read_input(trigger, &ret, &termcaps_context, pipefd) == ST_BREAK)
			break ;
	}
	termcaps_finalize(&termcaps_context);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (ret);
}
