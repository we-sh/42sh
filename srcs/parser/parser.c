#include "parser.h"

/*
** Delete the structure pointed by parser and return ST_OK on success.
** Otherwise (if the argument doesn't point to anything), it returns other code.
*/

static int		s_parser_callback(t_parser **parser)
{
	int			i;

	if (!(*parser))
		return (ST_EINVAL);
	i = 0;
	while (i < (*parser)->lexer->size)
	{
		free((*parser)->lexer->tokens[i]->content);
		free((*parser)->lexer->tokens[i]);
		i++;
	}
	free((*parser)->lexer->tokens);
	free((*parser)->lexer->buf);
	if ((*parser)->in)
		ft_strdel(&((*parser)->in));
	if ((*parser)->lexer)
	{
		free((*parser)->lexer);
		(*parser)->lexer = NULL;
	}
	free(*parser);
	*parser = NULL;
	return (ST_OK);
}

/*
** Call the main execution of the parser. It returns ST_OK on success (eg the
** parser/lexer doesn't failed). Otherwise (if the argument doesn't point to
** anything), it returns other code greater than 0.
*/

static int		s_parser_process(t_sh *sh, t_parser *parser_obj)
{
	int			ret;

	if (!sh || !parser_obj)
		return (ST_EINVAL);
	if ((ret = lexer(parser_obj, parser_obj->in)) != ST_OK)
		return (ret);
	if (!(parser_obj->lexer))
		return (ST_EINVAL);
	if (parser_obj->mode == F_PARSING_TERMCAPS)
		return (ST_OK);
	if ((ret = parser_build_list_unstack_lexer(parser_obj)) != ST_OK)
		return (ret);
	return (ST_OK);
}

/*
** Entry point of the parser.
** This function aims to build a list of shell jobs according to a string.
*/

int				parser(t_sh *sh, const char *in, int mode,
					t_list *target_list_head)
{
	int			ret;
	t_parser	*parser;

	if (!sh || !in)
		return (ST_EINVAL);
	log_trace("parser mode: %d `%s'", mode, in);
	if (mode == F_PARSING_TERMCAPS && in[0] == '\0')
		return (ST_OK);
	if ((ret = parser_new(&parser, in, sh, mode)) != ST_OK)
		return (ret);
	parser->target_list_head = target_list_head;
	ret = s_parser_process(sh, parser);
	s_parser_callback(&parser);
	return (ret);
}
