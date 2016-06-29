#include "shell.h"

t_job	*s_job_is_prefixed_by(char const *prefix, int const foreground)
{
	t_list	*j_pos;
	t_list	*j_head;
	t_job	*j;

	j_head = &g_current_jobs_list_head;
	j_pos = j_head;
	while ((j_pos = j_pos->prev) && j_pos != j_head)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == foreground)
			if (ft_strstr(j->command, prefix) == j->command)
				return (j);
	}
	return (NULL);
}

t_job	*s_job_contains(char const *str, int const foreground)
{
	t_list	*j_pos;
	t_list	*j_head;
	t_job	*j;

	j_head = &g_current_jobs_list_head;
	j_pos = j_head;
	while ((j_pos = j_pos->prev) && j_pos != j_head)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == foreground)
			if (ft_strstr(j->command, str) != NULL)
				return (j);
	}
	return (NULL);
}

t_job	*s_job_with_position(int const position, int const foreground)
{
	size_t	j_total;
	t_list	*j_pos;

	if (foreground == 0)
		return (job_background_nth(&g_current_jobs_list_head, position));
	j_total = list_size(&g_current_jobs_list_head);
	if (j_total == 0 || (position == -2 && j_total == 1))
		return (NULL);
	if ((j_pos = list_nth(&g_current_jobs_list_head, position)) == NULL)
		return (NULL);
	return (CONTAINER_OF(j_pos, t_job, list_job));
}

t_job	*job_by_name(char const *name, int foreground)
{
	if (!name || name[0] != '%' || name[1] == 0)
		return (NULL);
	if (ft_isdigit(name[1]))
		return (job_by_id(ft_atoi(name + 1), foreground));
	if (name[1] == '-')
		return (s_job_with_position(-2, foreground));
	if (name[1] == '%' || name[1] == '+')
		return (s_job_with_position(-1, foreground));
	if (name[1] == '?')
		return (s_job_contains(name + 2, foreground));
	return (s_job_is_prefixed_by(name + 1, foreground));
}
