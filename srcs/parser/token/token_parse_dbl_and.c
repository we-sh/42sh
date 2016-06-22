#include "parser.h"

int	token_parse_dbl_and(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&&'", "TT_JOBS");

	// todo: use parsing mode to customize what this function does
	if (parser->mode != F_PARSING_JOBS)
	{
		return (ST_OK);
	}

	t_job *j;
	j = (t_job *)target;
	j->separator = F_JSEP_AND_IF;

	(void)lexer;
	(void)i;
	/*
	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "&&");
		return (ST_PARSER);
	}
	p->j->separator = F_JSEP_AND_IF;
	*/
	return (0);
}
