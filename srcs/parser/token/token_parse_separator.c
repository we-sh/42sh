#include "shell.h"

int		token_parse_separator(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '\'", "TT_SEPARATOR");
	(void)target;
	(void)parser;
	(void)lexer;
	(void)i;

	if (parser->mode == F_PARSING_JOBS)
	{
		t_job *j;
		j = (t_job *)target;
		token_parse_utils_push_command(lexer->tokens[*i].content, &j->command);
	}
	(*i)++;
	return (0);
}
