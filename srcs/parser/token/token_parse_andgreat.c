/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_andgreat.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	content = TOKEN_CONTENT(*i);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		if (lexer->notify == 1)
			display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	(*i)--;
	return (ST_OK);
}

static int	s_jobs(t_job *j, t_lexer *lexer, int *i)
{
	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	int		fd;
	int		ret;

	ret = ST_OK;
	(*i)++;
	if (TOKEN_CONTENT(*i)[0] == '-')
	{
		fd = -1;
		ret = token_parse_utils_gen_token_after_dash(p, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	else
	{
		token_parse_utils_skip_separators(lexer, i, NULL);
		ret = token_parse_utils_open_new_fd(p,
				TOKEN_CONTENT(*i), &fd, O_WRONLY | O_CREAT | O_TRUNC);
	}
	if (fd == -1)
		token_parse_utils_set_proc_fds(p, STDOUT_FILENO, -1);
	else
		token_parse_utils_set_proc_fds(p, STDOUT_FILENO, STDERR_FILENO);
	token_parse_utils_set_proc_fds(p, STDERR_FILENO, fd);
	return (ret);
}

int			token_parse_andgreat(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	lexer->tokens[*i]->is_redir_checked = 1;
	ret = ST_OK;
	if (TOKEN_CODE(*i) != TC_ANDGREAT)
		return (lexer->tokens[*i]->parse(target, parser, lexer, i));
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, parser, lexer, i);
	(*i)++;
	return (ret);
}
