#include "parser.h"

/*
** Stub the creation of a job.
*/

static t_job	*s_job_create(char **array, char const *input)
{
	int		i;
	t_job	*j;
	t_list	*p_node;
	char	**p_array;

	if ((j = job_alloc(input)) == NULL)
		return (NULL);
	list_push_back(&j->list_job, &g_current_jobs_list_head);
	i = 0;
	while (array[i] != NULL)
	{
		p_array = ft_strsplit(array[i], ' ');
		if ((p_node = list_node__proc_alloc(array[i], p_array)) == NULL)
			return (NULL);
		// process redir
		list_push_back(p_node, &j->proc_head);
		i++;
	}
	return (j);
}

/*
** Convert an ast to a job structure.
*/

int				ast_to_jobs(t_list *ast_head, t_job *jobs, t_sh *sh)
{
	t_list		*pos;
	t_job	*job;
	int			i;
	int			exit_status;
	char		**array;
	char		*cleaned;

	i = 0;
	pos = ast_head;
	while ((pos = pos->next) && pos != ast_head)
	{
		job = CONTAINER_OF(pos, t_node_job, list);
		log_info("job %d : %s", i, job->cmd);
		cleaned = ft_strser(job->cmd);
		if (ft_strlen(cleaned) > 0 && (array = ft_strsplit(cleaned, '|')) != NULL)
		{
			if ((jobs = s_job_create(array, cleaned)) == NULL)
			{
				log_fatal("parse job");
				return (-1);
			}
			exit_status = job_launch(sh, jobs);
			if (exit_status != ST_OK)
			{
				log_fatal("job launch error: %s", i18n_translate(exit_status));
				return (exit_status);
			}
			ft_memdel_tab((void ***)&array);
		}
		ft_strdel(&cleaned);
		i++;
		tmp = tmp->next;
	}
	return (0);
}
