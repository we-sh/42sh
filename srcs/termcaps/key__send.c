#include "shell.h"

static int				s_fill_context_buffer(t_termcaps_context *context,
												char *buffer)
{
	t_list_node_cmd	*node_cmd;
	t_list			*pos;

	context->buffer = ft_strdup(buffer + context->prompt.size);
	if (!context->buffer)
		return (0);
	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (node_cmd->character[0] == '\n')
			node_cmd->character[0] = ' ';
	}
	return (1);
}

static int				s_bufferize_input(t_termcaps_context *context)
{
	size_t		buffer_size;
	char		buffer[2048];

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

static int				s_key__regular(t_termcaps_context *context)
{
	int					ret;
	size_t				command_line_cur_size;
	char				command_line_cur[2048];

	ASSERT(list_head__command_line_to_buffer(&context->command_line,
											sizeof(command_line_cur) - 1,
											&command_line_cur_size,
											command_line_cur));

	if ((ret = parser(context->sh, command_line_cur + 3, F_PARSING_TERMCAPS, NULL)) != ST_OK)
	{
		log_warn("should enter quoting context with token: %d", ret);
		//if ((ret = (quoting_new_context(context))) == ST_MALLOC)
		//	return (ret);
	}
	if (g_child == 0)
	{
		termcaps_display_command_line(context);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	}
	if (context->command_line.size > context->prompt.size)
	{
		if (!s_bufferize_input(context))
		{
			log_error("s_bufferize_input() failed");
			return (-1);
		}
	}
	else if (g_in_child == 2)
	{
		context->buffer = ft_strdup(" ");
		(void)write(context->fd, "\n", 1);
	}
	else
		(void)write(context->fd, "\n", 1);
	return (ST_OK);
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

int g_child = 0;
int g_in_child = 0;

int						key__send(t_termcaps_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		if ((s_key__regular(context)) != ST_OK)
			return (0);
		g_child = 0;
	}
	else if (context->state == STATE_SEARCH_HISTORY)
		s_key__search_hist(context);
	return (1);
}
