#include "shell.h"

int			token_var_parse_none(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;
	char	*output;

	ret = ST_OK;
	output = NULL;
	if ((ret = local_var_replace(parser->sh, TOKEN_CONTENT(*i), &output))
		!= ST_OK)
		return (ret);
	if (output[0] != '\0')
	{
		((t_argv *)target)->is_null = 0;
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
						output);
	}
	(*i)++;
	free(output);
	return (ret);
}
