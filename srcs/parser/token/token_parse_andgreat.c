#include "parser.h"

/*
** Operator: &>
** Type:     TT_REDIR
** Code:     TC_ANDGREAT
*/

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	content = TOKEN_CONTENT(*i);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
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
		ft_strcpy(TOKEN_CONTENT(*i), TOKEN_CONTENT(*i) + 1);
		lexer->tokens[*i]->type = TT_NAME;
		lexer->tokens[*i]->code = TC_NONE;
		lexer->tokens[*i]->parse = token_parse_none;
		ret = lexer->tokens[*i]->parse((void *)p, parser, lexer, i);
	}
	else
	{
		token_parse_utils_skip_separators(lexer, i, NULL);
		if (TOKEN_TYPE(*i) != TT_NAME)
			log_error("unexpected token `%s'", TOKEN_CONTENT(*i));
		ret = token_parse_utils_open_new_fd(p,
				TOKEN_CONTENT(*i), &fd, O_WRONLY | O_CREAT | O_APPEND);
	}
	// set the fds
	token_parse_utils_set_proc_fds(p, STDOUT_FILENO, fd == -1 ? -1 : STDERR_FILENO);
	token_parse_utils_set_proc_fds(p, STDERR_FILENO, fd);
	return (ret);
}

int			token_parse_andgreat(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&>'", "TT_REDIR");

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
