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
	t_job		*job;
	t_list		*pos;

	job_list_clean(1);
	job = NULL;
	if ((ret = parser_new(&parser, in)) != 0)
		return (ret);
	if ((ret = parser_process_lexer(parser->lexer, parser->in)) != 0)
		return (ret);
	if ((ret = parser_process_ast(&g_current_jobs_list_head, parser->lexer, sh->envp)) != 0)
		return (ret);
	LIST_FOREACH(&g_current_jobs_list_head, pos)
	{
		int	exit_status;
		job = CONTAINER_OF(pos, t_job, list_job);
		exit_status = job_launch(sh, job);
		if (exit_status != ST_OK)
		{
			log_fatal("job launch error: %s", i18n_translate(exit_status));
			return (exit_status);
		}

	}
	return (ST_OK);
}
