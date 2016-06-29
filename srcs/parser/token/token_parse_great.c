/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_great.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	s_proc_parse_right_part(t_proc *p, t_parser *parser, int *i,
				int *fd)
{
	int		ret;
	char	*path;

	token_parse_utils_skip_separators(parser->lexer, i, NULL);
	path = NULL;
	if ((ret = token_parse_utils_get_full_word(&path,
									parser->lexer, i)) != ST_OK)
		return (ret);
	if ((ret = token_parse_utils_open_new_fd(p, path, fd,
									O_WRONLY | O_CREAT | O_TRUNC)) != ST_OK)
		return (ret);
	free(path);
	(*i)--;
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	int		fd_l;
	int		fd_r;
	int		ret;

	fd_l = STDOUT_FILENO;
	if (TOKEN_CODE(*i) != TC_GREAT)
	{
		ret = token_parse_utils_check_char_to_fd(TOKEN_CONTENT(*i), &fd_l);
		if (ret != ST_OK)
		{
			ret = lexer->tokens[*i]->parse((void *)p, parser, lexer, i);
			if (ret != ST_OK)
				return (ret);
		}
		else
			(*i)++;
	}
	(*i)++;
	if ((ret = s_proc_parse_right_part(p, parser, i, &fd_r)) != ST_OK)
		return (ret);
	token_parse_utils_set_proc_fds(p, fd_l, fd_r);
	return (ST_OK);
}

static int	s_jobs(t_job *j, t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	if (TOKEN_CODE(*i) != TC_GREAT)
	{
		ret = lexer->tokens[*i]->parse((void *)j, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &(j->command));
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	if (TOKEN_CODE(*i) != TC_GREAT)
		(*i)++;
	content = TOKEN_CONTENT(*i);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		if (lexer->notify == 1)
			display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	return (ST_OK);
}

int			token_parse_great(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	lexer->tokens[*i]->is_redir_checked = 1;
	ret = ST_OK;
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
	{
		ret = s_proc((t_proc *)target, parser, lexer, i);
		if (ret != ST_OK)
			((t_proc *)target)->is_valid = 1;
	}
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, parser, lexer, i);
	(*i)++;
	return (ret);
}
