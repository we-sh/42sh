#include "shell.h"

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
** WARNING: ft_strsplit return array even if input length == 0
*/

t_job *s_job_create(char **array, char const *input)
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
		if ((p_node = list_node__proc_alloc(p_array)) == NULL)
			return (NULL);
		list_push_back(p_node, &j->proc_head);
		i++;
	}
	return (j);
}

int	parse(char const *input)
{
	int		ret;
	t_job	*j;
	char	*cleaned;
	char	**array;
	t_lexer l;

	j = NULL;
	cleaned = ft_strser(input);
	lexer(cleaned, &l);
	if (ft_strlen(cleaned) > 0 && (array = ft_strsplit(cleaned, '|')) != NULL)
	{
		if ((j = s_job_create(array, input)) == NULL)
			log_fatal("parse job");
		//ft_memdel_tab(array);
		if ((ret = job_launch(j)) != ST_OK)
			log_fatal("job launch error: %s", i18n_translate(ret));
	}
	ft_strdel(&cleaned);
	return (ST_OK);
}
