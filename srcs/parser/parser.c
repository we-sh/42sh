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

	log_info("entering parser with input >%s<\n", in);

	job_list_clean(1);
	job = NULL;
	if ((ret = parser_new(&parser, in)) != 0)
		return (ret);
	if ((ret = parser_process_lexer(parser->lexer, parser->in)) != 0)
		return (ret);
	if ((ret = parser_process_ast(&g_current_jobs_list_head, parser->lexer, sh->envp)) != 0)
		return (ret);

	log_warn("execution loop launched into the parser");
	LIST_FOREACH(&g_current_jobs_list_head, pos)
	{
		log_trace("%p", &g_current_jobs_list_head);
		log_trace("%p", CONTAINER_OF(&g_current_jobs_list_head, t_job, list_job));
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
