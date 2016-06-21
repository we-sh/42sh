#include "parser.h"

/*
** For each token of the lexer, apply a function and build a 'job-tree' into the
** global variable g_current_jobs_list_head.
*/

int	parser_build_list_unstack_lexer(t_parser *parser)
{
	int		i;
	int		ret;

	if (!parser)
		return (ST_EINVAL);
	i = 0;
	while (i < parser->lexer->size)
	{
		if ((ret = parser->unstack_func(parser, parser->lexer, &i)) != ST_OK)
		{
			log_warn("failed to unstack lexer");
			return (ret);
		}
	}
	log_success("parsing lexer into %zu jobs",
			list_size(parser->target_list_head));
	return (ST_OK);
}
