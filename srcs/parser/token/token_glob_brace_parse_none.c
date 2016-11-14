#include "shell.h"

int			token_glob_brace_parse_none(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;

	ret = ST_OK;
	(void)target;
	log_trace("--------- `%s`", TOKEN_CONTENT(*i));
	ret = token_globing_parse_utils_push_str(parser->target_list_head,
													TOKEN_CONTENT(*i));
	if (ret != ST_OK)
		return (ret);
	(void)lexer;
	(void)parser;
	(*i)++;
	return (ret);
}
