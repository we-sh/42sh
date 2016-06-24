#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/

static int	s_none(t_lexer *lexer, int *i)
{
	int		index;

	index = *i;
	while (index >= 0)
	{
		if (TOKEN_TYPE(index) == TT_NAME)
			return (ST_OK);
		index--;
	}
	log_error("eror");
	display_status(ST_PARSER_TOKEN, NULL, lexer->tokens[*i]->content);
	return (ST_PARSER);
}

static int	s_job(t_job *j, t_lexer *lexer, int *i)
{
	(void)lexer;
	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_lexer *lexer, int *i)
{
	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	return (ST_OK);
}

int			token_parse_pipe(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '|'", "TT_REDIR");

	int		ret;

	ret = ST_OK;
	lexer->tokens[*i]->is_redir_checked = 1;
	if (TOKEN_CODE(*i) != TC_PIPE)
		return (lexer->tokens[*i]->parse(target, parser, lexer, i));
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, lexer, i);
	(*i)++;
	return (ret);
}
