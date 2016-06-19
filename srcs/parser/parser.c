#include "parser.h"

/*
** Proceed to the parser process according to the structure.
** TODO remove the execution part of the function.
*/

static int	parser_process(t_sh *sh, t_parser *parser)
{
	int			st;

	if ((st = parser_process_lexer(parser->lexer, parser->in)) != ST_OK)
		return (st);
	if ((st = parser_process_build(parser->lexer, sh->envp)) != ST_OK)
		return (st);

	return (ST_OK);
}

static int	s_parser_callback(t_parser **parser)
{
	if (!(*parser))
		return (ST_EINVAL);
	if ((*parser)->in)
		ft_strdel(&((*parser)->in));
	if ((*parser)->lexer)
	{
		free((*parser)->lexer);
		(*parser)->lexer = NULL;
	}
	free(*parser);
	*parser = NULL;
	return (0);
}

/*
** Entry point of the parser.
** This function aims to build a list of shell jobs according to a string.
*/

int			parser(t_sh *sh, const char *in)
{
	int			st;
	t_parser	*parser;

	if (!sh || !in)
		return (ST_EINVAL);

	log_success("parser receives input : \"%s\"", in);

	if ((st = parser_new(&parser, in)) != ST_OK)
		return (st);

	st = parser_process(sh, parser);

	if ((s_parser_callback(&parser)) == ST_OK)
		log_success("parser deleted with success");
	else
		log_error("failed to delete parser");
	return (st);
}
