#include "parser.h"

/*
** Prepare the job list to default value for a new parser instance.
*/

static void	s_job_list_set_default(t_job **j)
{
	job_list_clean(1);
	*j = NULL;
}

/*
** Proceed to the parser process according to the structure.
** TODO remove the execution part of the function.
*/

static int	parser_process(t_sh *sh, t_parser *parser)
{
	int			st;
	t_job		*j;
	t_list		*j_ptr;

	s_job_list_set_default(&j);
	if ((st = parser_process_lexer(parser->lexer, parser->in)) != ST_OK)
		return (st);
	if ((st = parser_process_build(parser->lexer, sh->envp)) != ST_OK)
		return (st);

	LIST_FOREACH(&g_current_jobs_list_head, j_ptr)
	{
		int	st;
		j = CONTAINER_OF(j_ptr, t_job, list_job);
		// check for &&, || or ;
		st = job_launch(sh, j);
		if (st != ST_OK)
		{
			log_fatal("job launch error: %s", i18n_translate(st));
			return (st);
		}
	}
	return (ST_OK);
}

static void	s_parser_callback(t_parser **parser)
{
	if (!(*parser))
		return ;
	if ((*parser)->in)
		ft_strdel(&((*parser)->in));
	if ((*parser)->lexer)
	{
		free((*parser)->lexer);
		(*parser)->lexer = NULL;
	}
	free(*parser);
	*parser = NULL;
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
	
	s_parser_callback(&parser);
	return (st);
}
