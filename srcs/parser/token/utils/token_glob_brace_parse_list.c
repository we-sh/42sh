#include "shell.h"

static int		s_update_buffer(t_argv *el, char *original, char *suffix)
{
	if (el->buffer != NULL)
		free(el->buffer);
	if ((el->buffer = ft_strjoin(original, suffix)) == NULL)
		return (ST_MALLOC);
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
										t_parser *parser, int i)
{
	char	*original_str;

	if ((original_str = ft_strdup(argument->buffer)) == NULL)
		return (NULL);
	while (1)
	{
		if (s_update_buffer(argument, original_str, P_TOKEN_CONTENT(i)) != ST_OK)
			return (NULL);
		prev->next = &argument->argv_list;
		prev = &argument->argv_list;
		i++;
		while (P_TOKEN_CODE(i) == TC_COMMA)
			i++;
		if (P_TOKEN_CODE(i) == TC_RBRACE)
			break ;
		if ((argument = s_alloc_new_argv(prev)) == NULL)
			return (NULL);
	}
	free(original_str);
	return (argument);
}

int				token_glob_brace_parse_list(t_parser *parser,
											t_list *pos, int *i)
{
	t_list	*next;
	t_argv	*last_new;

	while ((pos = pos->next) && pos != parser->target_list_head)
	{
		next = pos->next;
		last_new = s_iterate_on_arguments(CONTAINER_OF(pos, t_argv, argv_list),
													pos, parser, *i + 1);
		if (last_new == NULL)
			return (ST_MALLOC);
		pos = &last_new->argv_list;
		last_new->argv_list.next = next;
		next->prev = &last_new->argv_list;
	}
	while (P_TOKEN_CODE(*i) != TC_RBRACE)
		*i += 1;
	return (ST_OK);
}
