#include "shell.h"

static int				s_termcaps_history_search_loop(
													t_termcaps_context *context,
													t_buffer *out_match,
													char *command)
{
	t_list				*pos;
	t_node_history	*history;
	size_t				history_offset;

	history_offset = context->history.offset;
	pos = list_nth(&context->history.list, history_offset + 1);
	while ((pos = pos->prev) && pos != &context->history.list)
	{
		history = CONTAINER_OF(pos, t_node_history, list);
		if (ft_strstr(history->command.bytes, command))
		{
			out_match->size = history->command.size;
			out_match->bytes = history->command.bytes;
			context->history.offset = history_offset;
			return (1);
		}
		history_offset--;
	}
	return (0);
}

int						termcaps_history_search(t_termcaps_context *context,
												t_buffer *out_match)
{
	char				command[TERMCAPS_BUFFER_MAX];
	size_t				command_size;

	out_match->size = 0;
	out_match->bytes = NULL;
	ASSERT(context->command.size > context->prompt.size);
	ASSERT(command_to_buffer(&context->command,
											sizeof(command) - 1,
											&command_size,
											command));
	command_size -= context->prompt.size;
	ft_memmove(command, command + context->prompt.size, command_size);
	command[command_size] = 0;
	ASSERT(s_termcaps_history_search_loop(context,
										out_match,
										command));
	return (1);
}
