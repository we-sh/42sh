#include "parser.h"

static t_proc	*ast_unstack_proc_from_lexer(t_lexer *lexer, int *i)
{
	t_proc	*proc;

	if ((proc = list_node__proc_alloc(array[i], p_array)) == NULL)
	{
		log_warn("TO IMPLEMENT display status");
		return (NULL);
	}

	while (*i < lexer->size && ret == 0)
	{
		log_debug("parsing token \"%s\"...", lexer->tokens[*i].content);

		if (lexer->tokens[*i].type == TT_NONE && lexer->tokens[(*i) + 1].type == TT_REDIR)
		{
			// tt_redir func get tt_none before
			ret = g_tokens[lexer->tokens[(*i) + 1].code].parse(proc, lexer, i);
		}
		else
			ret = g_tokens[lexer->tokens[*i].code].parse(proc, lexer, i);

		if (lexer->tokens[*i].type == TT_JOBS || lexer->tokens[*i].code == TC_PIPE)
		{
			log_info("end of job encountered, finish");
			break;
		}
		if (ret != ST_OK)
		{
			log_error("error on token parsing");
			log_warn("TO IMPLEMENT display status");
			return (NULL);
		}
		(*i)++;
	}
	return (proc);
}

static t_job	*ast_unstack_job_from_lexer(t_lexer *lexer, int *i)
{
	t_job	*job;
	t_proc	*proc;

	if (!(job = job_alloc("")))
		return (NULL);
	while (*i < lexer->size)
	{
		if (!(proc = ast_unstack_proc_from_lexer(lexer, i)))
			return (NULL);
		list_push_back(&proc->list_proc, &job->proc_head);
		if (lexer->tokens[*i].type == TT_JOBS)
			break;
	}
	return (job);
}

/*
** For each token of the lexer, apply a function and build an AST.
*/

int				ast_unstack_lexer(t_list *job_head, t_lexer *lexer)
{
	int		i;
	t_job	*job;

	i = 0;
	INIT_LIST_HEAD(job_head);
	while (i < lexer->size)
	{
		log_info("remaining tokens : %d / %d", lexer->size - i, lexer->size);
		if (!(job = ast_unstack_job_from_lexer(lexer, &i)))
			return (-1);
		list_push_back(&job->list_job, job_head);
	}
	return (0);
}
