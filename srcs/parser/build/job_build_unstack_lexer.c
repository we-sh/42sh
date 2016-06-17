#include "parser.h"

static int		s_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

/*
** Unstack processus from the stack of tokens.
*/

static t_proc	*ast_unstack_proc_from_lexer(t_lexer *lexer, int *i, char **envp)
{
	int		st;
	t_proc	*p;

	if ((p = proc_alloc(envp)) == NULL)
		return (NULL);

	while (*i < lexer->size)
	{
		log_success("%d", *i);
		log_debug("unstacking token : %d / %d : \"%s\"", *i, lexer->size, lexer->tokens[*i].content);
		log_debug(" %d / %d", lexer->tokens[*i].type, lexer->tokens[*i].code);

		if (lexer->tokens[*i].code == TC_NONE && *i + 1 < lexer->size && lexer->tokens[*i + 1].type == TT_REDIR)
			st = lexer->tokens[(*i) + 1].parse(p, lexer, i);
		else // TT_* standard (... ls ...)
			st = lexer->tokens[*i].parse(p, lexer, i);
		// detect and of job or process (see job_build_unstack_job_from_lexer)
		if (lexer->tokens[*i].type == TT_JOBS || lexer->tokens[*i].code == TC_PIPE)
			break;
		if (st != ST_OK)
		{
			log_error("error on token parsing");
			return (NULL);
		}
		(*i)++;
	}
	// replace with array push
	//if (!(p->argv = ft_strsplit(p->command, ' ')))
	//	return (NULL);
	p->argc = s_argc(p->argv);
	return (p);
}

/*
** Unstack the list of tokens to build a list of jobs.
*/

static t_job	*job_build_unstack_job_from_lexer(t_lexer *lexer, int *i, char **envp)
{
	t_job	*j;
	t_proc	*p;

	if (!(j = job_alloc("")))
		return (NULL);
	while (*i < lexer->size)
	{
		log_info("remaining tokens : %d / %d", lexer->size - *i, lexer->size);

		if (!(p = ast_unstack_proc_from_lexer(lexer, i, envp)))
			return (NULL);
		list_push_back(&p->list_proc, &j->proc_head);
		if (lexer->tokens[*i].type == TT_JOBS)
		{
			log_info("end of job encountered ('%s')", lexer->tokens[*i].content);
			(*i)++;
			break;
		}
		else if (lexer->tokens[*i].code == TC_PIPE)
		{
			log_info("end of processus encountered ('%s')", lexer->tokens[*i].content);
			(*i)++;
		}
		else
			log_info("remaining tokens : %d / %d", lexer->size - *i, lexer->size);
	}
	return (j);
}

/*
** For each token of the lexer, apply a function and build a 'job-tree' into the
** global variable g_current_jobs_list_head.
*/

int				job_build_unstack_lexer(t_lexer *lexer, char **envp)
{
	int		i;
	t_job	*j;

	i = 0;
	while (i < lexer->size)
	{
		if (!(j = job_build_unstack_job_from_lexer(lexer, &i, envp)))
			return (ST_PARSER);
		list_push_back(&j->list_job, &g_current_jobs_list_head);
	}
	log_success("parsing lexer into %zu jobs", list_size(&g_current_jobs_list_head));
	return (0);
}