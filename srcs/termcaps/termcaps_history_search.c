#include "shell.h"

#define REVERSE_I_SEARCH					"reverse-i-search: "
#define REVERSE_I_SEARCH_SIZE		(sizeof("reverse-i-search: ") - 1)

int	termcaps_history_search(t_termcaps_context *context, char **out_match)
{
	t_list_node_history	*history;
	t_list				*pos;
	char				command_line_cur[2048];
	size_t				command_line_cur_size;
	char				*match;
	size_t				history_offset;

	*out_match = NULL;
	if (context->command_line.size > context->prompt.size)
	{
		ASSERT(list_head__command_line_to_buffer(&context->command_line,
												 sizeof(command_line_cur) - 1,
												 &command_line_cur_size,
												 command_line_cur));
		history_offset = context->history.offset;
		pos = list_nth(&context->history.list, history_offset + 1);
		while ((pos = pos->prev) && pos != &context->history.list)
		{
			history = CONTAINER_OF(pos, t_list_node_history, list);
			history_offset--;
			match = history->command_line.bytes;
			if ((match = ft_strstr(match,
								   command_line_cur + context->prompt.size)) != NULL)
			{
				log_warn("%s", match);
				*out_match = ft_strjoin(REVERSE_I_SEARCH,
										history->command_line.bytes);
				if (*out_match == NULL)
					return (0);
				context->history.offset = history_offset;
				log_debug("history offset %zu size %zu", context->history.offset, context->history.size);
				log_success("%s", history->command_line.bytes);
				return (1);
			}
		}
	}
	*out_match = ft_strdup(REVERSE_I_SEARCH);
	if (*out_match == NULL)
		return (0);
	return (1);
}
