#include "parser.h"

static int		s_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

t_proc	*proc_alloc(char **envp)
{
	t_proc	*p;

	if (!(p = ft_memalloc(sizeof(t_proc))))
		return (NULL);
	if ((p->envp = ft_array_dup(envp)) == NULL)
		return (NULL);
	p->pid = 0;
	p->completed = 0;
	p->stopped = 0;
	p->signaled = 0;
	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	p->exit_status = EXIT_SUCCESS;
	p->bltin_status = ST_OK;
	INIT_LIST_HEAD(&p->bltin_opt_head);
	return (p);
}

static t_proc	*ast_unstack_proc_from_lexer(t_lexer *lexer, int *i, char **envp)
{
	t_proc	*proc;
	int		ret;

	if ((proc = proc_alloc(envp)) == NULL)
	{
		log_warn("TO IMPLEMENT display status");
		return (NULL);
	}

	while (*i < lexer->size)
	{
		log_debug("parsing token \"%s\"...", lexer->tokens[*i].content);

		if (lexer->tokens[*i].type == TT_NONE && *i + 1 < lexer->size && lexer->tokens[(*i) + 1].type == TT_REDIR)
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
	log_info("new proc parsed : %s", proc->command);

	if (!(proc->argv = ft_strsplit(proc->command, ' ')))
		return (NULL);
	proc->argc = s_argc(proc->argv);

	return (proc);
}

static t_job	*ast_unstack_job_from_lexer(t_lexer *lexer, int *i, char **envp)
{
	t_job	*job;
	t_proc	*proc;

	if (!(job = job_alloc("")))
		return (NULL);
	INIT_LIST_HEAD(&job->proc_head);
	while (*i < lexer->size)
	{
		if (!(proc = ast_unstack_proc_from_lexer(lexer, i, envp)))
			return (NULL);
		list_push_back(&proc->list_proc, &job->proc_head);
		if (lexer->tokens[*i].type == TT_JOBS)
		{
			log_warn("set flag for ; && or ||");
			(*i)++;
			break;
		}
	}

	
	log_info("finished to parse job");
	return (job);
}

/*
** For each token of the lexer, apply a function and build an AST.
*/

int				ast_unstack_lexer(t_list *job_head, t_lexer *lexer, char **envp)
{
	int		i;
	t_job	*job;

	i = 0;
	INIT_LIST_HEAD(job_head);
	while (i < lexer->size)
	{
		log_info("remaining tokens : %d / %d", lexer->size - i, lexer->size);
		if (!(job = ast_unstack_job_from_lexer(lexer, &i, envp)))
			return (-1);
		list_push_back(&job->list_job, job_head);
	}
	log_info("job list size : %zu", list_size(job_head));
	return (0);
}
