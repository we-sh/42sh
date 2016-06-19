#include "parser.h"

/*
** Unstack the list of tokens to build a list of jobs.
** TODO do not return the job whether it's an empty one
*/

t_job	*job_build_unstack_job_from_lexer(t_lexer *lexer, int *i, char **envp)
{
	t_job	*j;
	t_proc	*p;

	if (!(j = job_alloc("")))
		return (NULL);
	while (*i < lexer->size)
	{
		log_info("remaining tokens : %d / %d", lexer->size - *i, lexer->size);

		if (!(p = ast_unstack_proc_from_lexer(lexer, i, envp, j)))
			return (NULL);
		list_push_back(&p->list_proc, &j->proc_head);
		if (lexer->tokens[*i].type == TT_JOBS)
		{
			log_info("end of job encountered     ('%s')", lexer->tokens[*i].content);
			(*i)++;
			break ;
		}
		else if (lexer->tokens[*i].code == TC_PIPE)
		{
			log_info("end of process encountered ('%s')", lexer->tokens[*i].content);
			(*i)++;
		}
		else
			log_info("remaining tokens : %d / %d", lexer->size - *i, lexer->size);
	}
	return (j);
}
