#include "shell.h"

static int				s_fill_context_buffer(t_termcaps_context *context,
												char *buffer)
{
	t_list_node_cmd		*node_cmd;
	t_list				*safe;
	t_list				*pos;

	context->buffer = ft_strdup(buffer + context->prompt.size);
	if (!context->buffer)
		return (0);
	safe = context->command_line.list.next;
	while ((pos = safe) && (pos != &context->command_line.list))
	{
		safe = safe->next;
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (node_cmd->character[0] == '\n')
			node_cmd->character[0] = ' ';
	}
	return (1);
}

static int				s_bufferize_input(t_termcaps_context *context)
{
	size_t		buffer_size;
	char		buffer[TERMCAPS_BUFFER_MAX];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (0);
	}
	buffer[buffer_size] = '\0';
	if (!s_fill_context_buffer(context, buffer))
	{
		log_error("(s_fill_context_buffer() failed");
		return (0);
	}
	if (!key__share__command_line_to_history(context))
	{
		log_error("key__share__command_line_to_history() failed");
		return (0);
	}
	context->history.offset = context->history.size;
	return (1);
}

static int				s_key__search_hist(t_termcaps_context *context)
{
	t_list				*node;
	t_list_node_history	*history;

	node = list_nth(&context->history.list, context->history.offset);
	if (node != &context->history.list)
	{
		list_head__command_line_destroy(&context->command_line);
		list_head__init(&context->command_line);
		history = CONTAINER_OF(node, t_list_node_history, list);
		ASSERT(termcaps_string_to_command_line(context->prompt.size,
												context->prompt.bytes,
												&context->command_line));
		ASSERT(termcaps_string_to_command_line(history->command_line.size,
												history->command_line.bytes,
												&context->command_line));
	}
	context->history.offset = context->history.size;
	context->state = STATE_REGULAR;
	return (1);
}

int						s_key_send(t_termcaps_context *context)
{
	size_t				command_line_cur_size;
	char				command_line_cur[TERMCAPS_BUFFER_MAX];
	int					ret;

	if (list_head__command_line_to_buffer(&context->command_line,
sizeof(command_line_cur) - 1, &command_line_cur_size, command_line_cur))
	{
		command_line_cur[command_line_cur_size] = 0;
		if (context->option != OPTION_HEREDOC &&
			(ret = parser(context->sh, command_line_cur + context->prompt.size,
						  F_PARSING_TERMCAPS, NULL)) != ST_OK)
			quoting_new_context(context, ret);
	}
	if (context->child == 0)
	{
		termcaps_display_command_line(context);
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
		if (context->command_line.size > context->prompt.size)
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
