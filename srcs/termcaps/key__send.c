#include "shell.h"

/**/
int					builtin_history(t_termcaps_context *context, char *buffer, int *is_history)
{
	t_list							*node;
	t_node_history	*node_history;
	int									index;
	t_buffer						match;

	*is_history = 1;
	index = 0;
	if (ft_isdigit(buffer[1]) ||
			(buffer[1] == '-' && ft_isdigit(buffer[2])))
		index = ft_atoi(buffer + 1);
	else if (buffer[1] == '!')
		index = -1;
	else if (buffer[1] != '\0')
	{
		index = history_search(&context->history, buffer + 1);
		ASSERT(index != -1);
	}
	else
	{
		*is_history = 0;
		return (1);
	}
	node = list_nth(&context->history.list, index);
	ASSERT(node != &context->history.list);
	node_history = CONTAINER_OF(node, t_node_history, list);
	match = node_history->command;
	ASSERT(context->buffer = (char *)malloc(match.size + 1));
	ft_memcpy(context->buffer, match.bytes, match.size);
	context->buffer[match.size] = '\0';
	log_debug("context->buffer %s", context->buffer);
	return (1);
}
/**/

static int				s_fill_context_buffer(t_termcaps_context *context,
												char *buffer)
{
	t_node_cmd		*node_cmd;
	t_list				*safe;
	t_list				*pos;

	context->buffer = ft_strdup(buffer);
	if (!context->buffer)
		return (0);
	safe = context->command.list.next;
	while ((pos = safe) && (pos != &context->command.list))
	{
		safe = safe->next;
		node_cmd = CONTAINER_OF(pos, t_node_cmd, list);
		if (node_cmd->character[0] == '\n')
			node_cmd->character[0] = ' ';
	}
	return (1);
}

static int				s_bufferize_input(t_termcaps_context *context)
{
	size_t		buffer_size;
	char		buffer[TERMCAPS_BUFFER_MAX];
	int			is_history;

	is_history = 0;
	if (!command_to_buffer(&context->command,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("command_to_buffer() failed");
		return (0);
	}
	buffer_size -= context->prompt.size;
	ft_memmove(buffer, buffer + context->prompt.size, buffer_size);
	buffer[buffer_size] = '\0';
	if (buffer[0] == '!' && !ft_isspace(buffer[1]))
	{
		ASSERT(builtin_history(context, buffer, &is_history));
		if (is_history)
		{
			command_clear(&context->command);
		}
	}
	if (!is_history)
	{
		ASSERT(s_fill_context_buffer(context, buffer));
		ASSERT(history_add(buffer, &context->history));
		command_clear(&context->command);
	}
	context->history.offset = context->history.size;
	return (1);
}

static int				s_key__search_hist(t_termcaps_context *context)
{
	t_list				*node;
	t_node_history	*history;

	node = list_nth(&context->history.list, context->history.offset);
	if (node != &context->history.list)
	{
		command_clear(&context->command);
		list_head__init(&context->command);
		history = CONTAINER_OF(node, t_node_history, list);
		ASSERT(command_add_string(context->prompt.size,
												context->prompt.bytes,
												&context->command));
		ASSERT(command_add_string(history->command.size,
												history->command.bytes,
												&context->command));
	}
	context->history.offset = context->history.size;
	context->state = STATE_REGULAR;
	return (1);
}

int						s_key_send(t_termcaps_context *context)
{
	size_t				command_cur_size;
	char				command_cur[TERMCAPS_BUFFER_MAX];
	int					ret;

	if (command_to_buffer(&context->command,
sizeof(command_cur) - 1, &command_cur_size, command_cur))
	{
		command_cur[command_cur_size] = 0;
		if (context->option != OPTION_HEREDOC &&
			(ret = parser(context->sh, command_cur + context->prompt.size,
						  F_PARSING_TERMCAPS, NULL)) != ST_OK)
			quoting_new_context(context, ret);
	}
	if (context->child == 0)
	{
		termcaps_display_command(context);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	}
	context->child = 0;
	return (1);
}

int						key__send(t_termcaps_context *context)
{
	if (context->state == STATE_SELECTION)
		key__select(context);
	if (context->state == STATE_REGULAR)
	{
		s_key_send(context);
		if (context->command.size > context->prompt.size)
		{
			ASSERT(s_bufferize_input(context));
		}
		else
			termcaps_write(context->fd, "\n", sizeof("\n") - 1);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
		s_key__search_hist(context);
	return (1);
}
