#include "parser.h"

/*
** Prepare the job list to default value for a new parser instance.
*/

static void	s_job_list_set_default(t_job **j)
{
	job_list_clean(1);
	*j = NULL;
}

int			parser(t_sh *sh, const char *in)
{
	int			st;
	t_parser	*parser;
	t_job		*j;
	t_list		*pos;

	log_info("parser receives input : \"%s\"\n", in);

	s_job_list_set_default(&j);
	if ((st = parser_new(&parser, in)) != ST_OK)
		return (st);
	if ((st = parser_process_lexer(parser->lexer, parser->in)) != ST_OK)
		return (st);
	if ((st = parser_process_ast(&g_current_jobs_list_head, parser->lexer, sh->envp)) != ST_OK)
		return (st);

	log_warn("execution loop launched into the parser");
	LIST_FOREACH(&g_current_jobs_list_head, pos)
	{
		log_trace("%p", &g_current_jobs_list_head);
		log_trace("%p", CONTAINER_OF(&g_current_jobs_list_head, t_job, list_job));
		int	exit_status;
		j = CONTAINER_OF(pos, t_job, list_job);
		exit_status = job_launch(sh, j);
		if (exit_status != ST_OK)
		{
			log_fatal("job launch error: %s", i18n_translate(exit_status));
			return (exit_status);
		}

	}
	return (ST_OK);
}
