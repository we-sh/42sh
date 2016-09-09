#include "shell.h"

static int				s_fill_context_buffer(t_termcaps_context *context,
												char *buffer)
{
	t_node_cmd		*node_cmd;
	t_list			*pos;

	context->buffer = ft_strdup(buffer);
	if (!context->buffer)
		return (0);
	pos = &context->command.list;
	while ((pos = pos->next) && (pos != &context->command.list))
	{
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
	t_buffer	buf;

	if (!command_to_buffer(&context->command,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		termcaps_error(context, "", 0, "Command line too big");
		return (0);
	}
	buffer_size -= context->prompt.size;
	ft_memmove(buffer, &buffer[context->prompt.size], buffer_size);
	buffer[buffer_size] = '\0';
	buf.bytes = buffer;
	buf.size = buffer_size;
	if (!replace_events(context, sizeof(buffer), &buf))
		return (0);
	ASSERT(s_fill_context_buffer(context, buffer));
	ASSERT(history_add(buffer, &context->history));
	command_clear(&context->command);
	context->history.offset = context->history.size;
	log_debug("context->buffer %s", context->buffer);
	return (1);
}

static int				s_search_hist(t_termcaps_context *context)
{
	t_list			*node;
	t_node_history	*history;

	node = list_nth(&context->history.list, context->history.offset);
	if (node != &context->history.list)
	{
		command_clear(&context->command);
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

void					s_check_quoting(t_termcaps_context *context)
{
	size_t		command_cur_size;
	char		command_cur[TERMCAPS_BUFFER_MAX];
	int			ret;

	if (command_to_buffer(&context->command,
				sizeof(command_cur) - 1,
				&command_cur_size,
				command_cur))
	{
		command_cur[command_cur_size] = 0;
		if (context->option != OPTION_HEREDOC &&
			(ret = parser(context->sh,
						command_cur + context->prompt.size,
						F_PARSING_TERMCAPS,
						NULL)) != ST_OK)
			quoting_new_context(context, ret);
	}
	if (context->child == 0)
	{
		termcaps_display_command(context);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	}
	context->child = 0;
}

int						key__send(t_termcaps_context *context)
{
	if (context->state == STATE_SELECTION)
		key__select(context);
	if (context->state == STATE_REGULAR)
	{
		s_check_quoting(context);
		if (context->command.size > context->prompt.size)
		{
			if (!s_bufferize_input(context))
				return (0);
		}
		else
			termcaps_write(context->fd, "\n", sizeof("\n") - 1);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
		s_search_hist(context);
	return (1);
}
