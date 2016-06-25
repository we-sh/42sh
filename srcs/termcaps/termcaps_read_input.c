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

static void			s_delete_line_context(t_termcaps_context *context,
							const t_buffer history_search)
{
	if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
	{
		caps__delete_line(context->command_line.offset);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		caps__delete_line(history_search.size +
						context->command_line.size - context->prompt.size +
						sizeof("reverse-i-search '' : ") - 2);
	}
}

static int			s_termcaps_read_loop(t_termcaps_context *context,
									size_t input_buffer_size,
									size_t input_size_missing)
{
	char			input_buffer[INPUT_SIZE_MAX];
	t_input_type	input_type;
	t_buffer		history_search;

	while (context->buffer == NULL)
	{
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
			s_delete_line_context(context, history_search);
			s_termcaps_treat_input(input_type, input_buffer_size, input_buffer,
									context);
			ASSERT(termcaps_display_context(context, &history_search));
		}
	}
	return (1);
}

int			set_new_prompt(t_termcaps_context *context)
{
	char 	*tmp;

	free(context->prompt.bytes);
	if ((tmp = env_get(context->sh->envp, "PS1")) == NULL)
		tmp = shell_set_prompt(context->sh->envp);
	context->prompt.size = ft_strlen(tmp);
	context->prompt.bytes = ft_strdup(tmp);
	return (ST_OK);
}

char				*termcaps_read_input(t_termcaps_context *context)
{
	int				x;
	size_t			input_buffer_size;
	size_t			input_size_missing;

	input_buffer_size = 0;
	input_size_missing = 0;
	ASSERT(context != NULL && context->is_initialized);
	ASSERT(!tcsetattr(context->fd, TCSADRAIN, &context->termios_new));
	ASSERT(caps__cursor_getxy(&x, NULL));
	if (x != 1)
		termcaps_write(context->fd, "%\n", sizeof("%\n") - 1);
	
	set_new_prompt(context);
	ASSERT(termcaps_string_to_command_line(context->prompt.size,
											context->prompt.bytes,
											&context->command_line));
	ASSERT(termcaps_display_command_line(context));
	context->state = STATE_REGULAR;
	context->buffer = NULL;
	ASSERT(s_termcaps_read_loop(context, input_buffer_size,
		input_size_missing));
	ASSERT(!tcsetattr(context->fd, TCSAFLUSH, &context->termios_old));
	return (context->buffer);
}
