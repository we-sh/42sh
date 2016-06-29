#include "shell.h"

int		token_parse_utils_gen_token_after_dash(t_proc *p, t_parser *parser,
			t_lexer *lexer, int *i)
{
	ft_strcpy(TOKEN_CONTENT(*i), TOKEN_CONTENT(*i) + 1);
	if (lexer->tokens[*i]->content[0] != '\0')
	{
		lexer->tokens[*i]->type = TT_NAME;
		lexer->tokens[*i]->code = TC_NONE;
		lexer->tokens[*i]->parse = token_parse_none;
		return (lexer->tokens[*i]->parse((void *)p, parser, lexer, i));
	}
	return (ST_OK);
}
