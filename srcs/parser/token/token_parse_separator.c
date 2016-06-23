#include "shell.h"

int		s_job(t_job *j, t_lexer *lexer, int *i)
{
	(void)lexer;
	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	return (ST_OK);
}

int		token_parse_separator(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '\'", "TT_SEPARATOR");

	int	ret;

	if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target, lexer, i);
	(*i)++;
	return (0);
}
