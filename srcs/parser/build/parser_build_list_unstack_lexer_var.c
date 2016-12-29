#include "parser.h"

static t_argv	*s_argv_alloc(void)
{
	t_argv		*argument;

	argument = (t_argv *)malloc(sizeof(t_argv));
	if ((argument->buffer = ft_strnew(0)) == NULL)
		return (NULL);
	argument->is_null = 1;
	return (argument);
}

int				parser_build_list_unstack_lexer_var(t_parser *parser,
					t_lexer *lexer, int *i)
{
	int			ret;
	t_argv		*argument;

	if (!(argument = s_argv_alloc()))
		return (ST_MALLOC);
	list_push_back(&argument->argv_list, parser->target_list_head);
	while (*i < lexer->size)
	{
		ret = lexer->tokens[*i]->parse((void *)argument, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	return (ST_OK);
}
