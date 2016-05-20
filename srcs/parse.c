#include "shell.h"

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
** WARNING: ft_strsplit return array even if input length == 0
*/

int	parse(char const *input)
{
	int		ret;
	t_list	*p_node;
	t_job	*j;
	char	*cleaned;
	char	**array;

	INIT_LIST_HEAD(&g_current_jobs_list_head);
	cleaned = ft_strser(input);
	if (ft_strlen(cleaned) > 0 && (array = ft_strsplit(cleaned, ' ')) != NULL)
	{
		if ((j = job_alloc((char *)input)) == NULL)
			return (ST_MALLOC);
		list_push_back(&j->list_job, &g_current_jobs_list_head);

		if ((p_node = list_node__proc_alloc(array)) == NULL)
			return (ST_MALLOC);
		list_push_back(p_node, &j->proc_head);

		if ((ret = job_launch(j)) != ST_OK)
			log_fatal("job launch error: %s\n", i18n_translate(ret));
		/* TODO: free array */
	}
	ft_strdel(&cleaned);
	return (ST_OK);
}
