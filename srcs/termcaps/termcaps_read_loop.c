#include "shell.h"

static int			s_termcaps_treat_input(const t_input_type it,
										const size_t ib_size,
										const char *ib,
										t_termcaps_context *context)
{
	if (it == MINISHELL__INPUT_TYPE_PRINT)
	{
		ASSERT(termcaps_string_to_command_line(ib_size,
											ib,
											&context->command_line));
	}
	else if (it == MINISHELL__INPUT_TYPE_CAPS)
	{
		caps__exec_func(ib_size, ib, context);
	}
	return (1);
}

static int			s_check_job_status(t_termcaps_context *context)
{
	if (job_background_update_status() > 0)
	{
		caps__delete_line(context->command_line.offset);
		ASSERT(termcaps_display_command_line(context));
		caps__cursor_to_offset(context->command_line.offset,
								context->command_line.size);
	}
	return (1);
}

int					termcaps_read_loop(t_termcaps_context *context,
									size_t ib_size,
									size_t input_size_missing)
{
	char			ib[INPUT_SIZE_MAX];
	t_input_type	it;
	t_buffer		history_search;

	while (context->buffer == NULL)
	{
		ft_bzero(ib, ft_strlen(ib));
		ib_size = read(context->fd, ib, 1);
		if (ib_size == 0)
			s_check_job_status(context);
		else if (ib_size == 1)
		{
			termcaps_identify_input(ib[0], &it, &input_size_missing);
			ASSERT(ib_size + input_size_missing <= sizeof(ib));
			if (input_size_missing)
				ib_size += read(context->fd, ib + 1,
					input_size_missing);
			termcaps_line_erase(context, history_search);
			s_termcaps_treat_input(it, ib_size, ib, context);
			ASSERT(termcaps_line_print(context, &history_search));
		}
		else
			return (ST_READ);
	}
	return (1);
}
