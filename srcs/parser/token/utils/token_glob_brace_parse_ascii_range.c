#include "shell.h"

static int		s_update_buffer_itoa(t_argv *el, char *original, int value)
{
	char	*tmp;

	if ((tmp = ft_strnew(1)) == NULL)
		return (ST_MALLOC);
	tmp[0] = (char)value;
	if (el->buffer != NULL)
		free(el->buffer);
	if ((el->buffer = ft_strjoin(original, tmp)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	return (ST_OK);
}

static t_argv	*s_alloc_new_argv(t_list *prev)
{
	t_argv	*argument;

	if ((argument = (t_argv *)malloc(sizeof(t_argv))) == NULL)
		return (NULL);
	argument->buffer = NULL;
	argument->argv_list.prev = prev;
	argument->argv_list.next = NULL;
	argument->is_null = 0;
	return (argument);
}

static t_argv	*s_iterate_on_arguments(t_argv *argument, t_list *prev,
										int start_original, int end)
{
	int		start;
	int		dir;
	char	*original_str;

	if ((original_str = ft_strdup(argument->buffer)) == NULL)
		return (NULL);
	start = start_original;
	dir = start > end ? -1 : 1;
	while (1)
	{
		if (start != start_original)
			if ((argument = s_alloc_new_argv(prev)) == NULL)
				return (NULL);
		if (s_update_buffer_itoa(argument, original_str, start) != ST_OK)
			return (NULL);
		prev->next = &argument->argv_list;
		if (start == end)
			break ;
		start += dir;
		prev = &argument->argv_list;
	}
	free(original_str);
	return (argument);
}

int				token_glob_brace_parse_ascii_range(t_parser *parser,
											t_list *pos, int *i)
{
	int		start_original;
	int		end;
	t_list	*next;
	t_argv	*last_new;

	start_original = (int)P_TOKEN_CONTENT(*i + 1)[0];
	end = (int)P_TOKEN_CONTENT(*i + 3)[0];
	while ((pos = pos->next) && pos != parser->target_list_head)
	{
		next = pos->next;
		last_new = s_iterate_on_arguments(CONTAINER_OF(pos, t_argv, argv_list),
													pos, start_original, end);
		if (last_new == NULL)
			return (ST_MALLOC);
		pos = &last_new->argv_list;
		last_new->argv_list.next = next;
		next->prev = &last_new->argv_list;
	}
	*i += 4;
	return (ST_OK);
}
