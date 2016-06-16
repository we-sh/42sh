#include "shell.h"

/*
** Display the token list on the logger.
*/

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

/*
** Convert an input string into a token list.
*/

int			parser_process_lexer(t_lexer *lexer, const char *in)
{
	if (!lexer || !in)
		return (ST_EINVAL);

	log_info("lexer receives input : \"%s\"", in);
	
	lexer->size = 0;
	if (tokenize(in, lexer) != ST_OK)
	{
		log_error("tokenization failed (incomplete inhibition)");
		return (ST_LEXER);
	}
	else
	{
		log_success("tokenization succeded, extract %d tokens", lexer->size);
		s_print(lexer);
	}
	return (ST_OK);
}
