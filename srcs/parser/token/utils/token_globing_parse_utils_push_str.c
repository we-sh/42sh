#include "shell.h"

int			token_globing_parse_utils_push_str(t_list *head, char *str)
{
	t_list	*pos;
	t_argv	*argument;
	char	*tmp;

	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		tmp = argument->buffer;
		if ((argument->buffer = ft_strjoin(argument->buffer, str)) == NULL)
			return (ST_MALLOC);
		free(tmp);
	}
	return (ST_OK);
}
