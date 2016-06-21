#include "parser.h"

/*
** Create a new parser structure and initialize its fields.
** The input string is duplicated and the other are allocated.
*/

int	parser_new(t_parser **parser, const char *in, t_sh *sh, int mode)
{
	if (!in)
		return (ST_EINVAL);
	if (!(*parser = ft_memalloc(sizeof(t_parser))))
		return (ST_MALLOC);
	if (!((*parser)->in = ft_strdup(in)))
		return (ST_MALLOC);
	if (!((*parser)->lexer = ft_memalloc(sizeof(t_lexer))))
		return (ST_MALLOC);
	(*parser)->lexer->sh = sh;
	// TODO : make dynamic token list
	(*parser)->mode = mode;
	(*parser)->target_list_head = NULL;
	return (ST_OK);
}
