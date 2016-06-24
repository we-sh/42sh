#include "shell.h"

int		token_parse_utils_gen_token_after_dash(t_proc *p, t_parser *parser,
			t_lexer *lexer, int *i)
{
	ft_strcpy(P_TOKEN_CONTENT(*i), P_TOKEN_CONTENT(*i) + 1);
	parser->lexer->tokens[*i].type = TT_NAME;
	parser->lexer->tokens[*i].code = TC_NONE;
	parser->lexer->tokens[*i].parse = token_parse_none;
	return (parser->lexer->tokens[*i].parse((void *)p, parser, lexer, i));
}
