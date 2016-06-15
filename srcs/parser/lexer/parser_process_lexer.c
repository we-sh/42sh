#include "shell.h"

static void	s_print(const t_lexer *lexer)
{
	int i;

	i = 0;
	while (i < lexer->size)
	{
		log_debug("tokens[%d] \"%s\" (type: %d, code: %d)", i,
				lexer->tokens[i].content, lexer->tokens[i].type,
				lexer->tokens[i].code);
		i++;
	}
}

int			parser_process_lexer(t_lexer *lexer, char const *input)
{
	log_info("receiving input : \"%s\"", input);
	lexer->size = 0;
	if (tokenize(input, lexer) != ST_OK)
	{
		log_error("tokenization failed (incomplete inhibition)");
		return (ST_LEXER);
	}
	s_print(lexer);
	return (ST_OK);
}
