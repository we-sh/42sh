#include "parser.h"

static int	s_job(t_job *j, t_lexer *lexer, int *i)
{
	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_lexer *lexer, int *i)
{
	int		ret;

	if (*i > 0 && TOKEN_TYPE(*i - 1) == TT_INHIBITOR)
		(*i)--;
	if ((ret = expand(lexer, p, i)) != ST_OK)
	{
		log_fatal("failed to expand at token #%d (content: `%s')", *i, TOKEN_CONTENT(*i));
		return (ret);
	}
	(*i)--;
	return (ST_OK);
}

int	token_parse_none(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d) (content:`%s')", "TT_NONE", lexer->tokens[*i]->type, lexer->tokens[*i]->code, TOKEN_CONTENT(*i));

	int		ret;

	ret = ST_OK;
	if (TOKEN_TYPE(*i) == TT_ERROR)
		return (ST_PARSER);
	if (lexer->tokens[*i]->is_redir_checked == 0
		&& *i + 1 < lexer->size && TOKEN_TYPE(*i + 1) == TT_REDIR && TOKEN_CODE(*i + 1) != TC_PIPE)
		return (lexer->tokens[*i + 1]->parse(target, parser, lexer, i));
	if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, lexer, i);
	(*i)++;
	return (ret);
}
