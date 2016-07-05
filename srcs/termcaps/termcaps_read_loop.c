#include "shell.h"

static int			s_termcaps_treat_input(const t_input_type input_type,
										const size_t input_buffer_size,
										const char *input_buffer,
										t_termcaps_context *context)
{
	if (input_type == MINISHELL__INPUT_TYPE_PRINT)
	{
		ASSERT(termcaps_string_to_command_line(input_buffer_size,
											input_buffer,
											&context->command_line));
	}
	else if (input_type == MINISHELL__INPUT_TYPE_CAPS)
	{
		caps__exec_func(input_buffer_size, input_buffer, context);
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
									size_t input_buffer_size,
									size_t input_size_missing)
{
	char			input_buffer[INPUT_SIZE_MAX];
	t_input_type	input_type;
	t_buffer		history_search;

	while (context->buffer == NULL)
	{
		input_buffer_size = 0;
		ft_bzero(input_buffer, ft_strlen(input_buffer));
		input_buffer_size = read(context->fd, input_buffer, 1);
		if (input_buffer_size == 0)
			s_check_job_status(context);
		else if (input_buffer_size == 1)
		{
			termcaps_identify_input(input_buffer[0], &input_type,
										&input_size_missing);
			ASSERT(input_buffer_size + input_size_missing <=
				sizeof(input_buffer));
			if (input_size_missing)
				input_buffer_size += read(context->fd, input_buffer + 1,
					input_size_missing);
			termcaps_line_erase(context, history_search);
			s_termcaps_treat_input(input_type, input_buffer_size, input_buffer,
									context);
			ASSERT(termcaps_line_print(context, &history_search));
		}
	}
	return (1);
}
