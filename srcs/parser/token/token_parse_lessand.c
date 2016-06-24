#include "shell.h"

int			token_parse_lessand(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	(void)target;
	(void)lexer;
	(void)parser;
	(*i)++;
	return (ST_OK);
}
