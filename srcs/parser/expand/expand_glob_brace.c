#include "shell.h"

int			expand_glob_brace(t_sh *sh, t_list **argv_list)
{
	int		ret;
	t_list	*new_argv_list;
	t_argv	*argument;
	t_list	*pos;
	t_list	*safe;

	if ((new_argv_list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (ST_MALLOC);
	INIT_LIST_HEAD(new_argv_list);
	safe = (*argv_list)->next;
	while ((pos = safe) && safe != *argv_list)
	{
		safe = safe->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		if ((ret = parser(sh, argument->buffer, F_PARSING_GLOB_BRACE,
													new_argv_list)) != ST_OK)
			return (ret);
		free(argument->buffer);
		free(argument);
	}
	free(*argv_list);
	*argv_list = new_argv_list;
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}
