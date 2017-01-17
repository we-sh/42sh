#include "shell.h"

int				lexer_buffer_dump(t_parser *parser, t_lexer *lexer)
{
	t_token		t;

	if (lexer->buf_index > 0)
	{
		lexer->buf[lexer->buf_index] = '\0';
		t.len = lexer->buf_index;
		t.type = TT_NAME;
		t.code = TC_NONE;
		if (parser->mode == F_PARSING_VAR)
			t.parse = token_var_parse_none;
		else if (parser->mode == F_PARSING_GLOB_BRACE)
			t.parse = token_glob_brace_parse_none;
		else
			t.parse = token_parse_none;
		if (lexer_token_add(lexer, lexer->buf, t) != ST_OK)
			return (ST_MALLOC);
		ft_bzero(lexer->buf, lexer->buf_allocated_size);
		lexer->buf_index = 0;
	}
	return (ST_OK);
}
