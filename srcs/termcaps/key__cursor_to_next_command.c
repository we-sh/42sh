#include "shell.h"

static int				s_get_next_command(t_internal_context *context)
{
	t_list				*history_entry;
	t_list_node_history	*history_node;

	history_entry = list_nth(&context->history.list,
			context->history.offset + 1);
	history_node = CONTAINER_OF(history_entry,
			t_list_node_history, list);
	if (!list_head__command_line_dup(&context->command_line,
				&history_node->command_line))
	{
		log_error("list_head__command_line_dup() failed %s");
		return (0);
	}
	context->command_line.offset = context->command_line.size;
	return (1);
}

int						key__cursor_to_next_command(t_internal_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		if (context->history.offset == context->history.size)
			return (1);
		list_head__command_line_destroy(&context->command_line);
		list_head__init(&context->command_line);
		context->command_line.offset = 0;
		context->history.offset += 1;
		if (context->history.offset == context->history.size)
		{
			if (!termcaps_string_to_command_line(PROMPT_SIZE, PROMPT,
						&context->command_line))
			{
				log_error("minishell__string_to_command_line() failed %s", PROMPT);
				return (0);
			}
		}
		else
		{
			return (s_get_next_command(context));
		}
	}
	return (1);
}
