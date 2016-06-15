#include "parser.h"

/*
** Entry point of the parser :
** lexer (token) -> parser (ast) -> jobs (convert tree to jobs)
** TODO : split the execution part
*/

int	parser(t_sh *sh, const char *in)
{
	int			ret;
	t_parser	*parser;
	t_job		*jobs;

	job_list_clean(1);
	jobs = NULL;
	if ((ret = parser_new(&parser, in)) != 0)
		return (ret);
	if ((ret = parser_process_lexer(parser->lexer, parser->in)) != 0)
		return (ret);
	if ((ret = parser_process_ast(&parser->ast_head, parser->lexer)) != 0)
		return (ret);
	if ((ret = ast_to_jobs(&parser->ast_head, jobs, sh)) != 0)
		return (ret);
	return (ST_OK);
}
