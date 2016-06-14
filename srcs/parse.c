#include "shell.h"

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
** WARNING: ft_strsplit return array even if input length == 0
*/

t_job *s_job_create(char **array, char const *input, char **envp)
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
		if ((p_node = list_node__proc_alloc(array[i], p_array, envp)) == NULL)
			return (NULL);
		list_push_back(p_node, &j->proc_head);
		i++;
	}

	// temporary to test background jobs
	char **tmp = ft_strsplit(input, ' ');
	i = 0;
	while (tmp[i])
	{
		if (ft_strcmp(tmp[i], "&") == 0)
			j->foreground = 0;
		i++;
	}
	ft_memdel_tab((void ***)&tmp);
	return (j);
}

int	parse(t_sh *sh, char const *input)
{
	int		exit_status;
	t_job	*j;
	char	*cleaned;
	char	**array;
	t_lexer l;

	job_list_clean(1);
	j = NULL;
	cleaned = ft_strser(input);
	lexer(cleaned, &l);	
	if (ft_strlen(cleaned) > 0 && (array = ft_strsplit(cleaned, '|')) != NULL)
	{
		if ((j = s_job_create(array, input, sh->envp)) == NULL)
		{
			log_fatal("parse job");
			return (-1);
		}
		ft_memdel_tab((void ***)&array);
		exit_status = job_launch(sh, j);
		if (exit_status != ST_OK)
		{
			log_fatal("job launch error: %s", i18n_translate(exit_status));
			return (exit_status);
		}
	}
	ft_strdel(&cleaned);
	return (ST_OK);
}
