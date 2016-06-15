#include "shell.h"

static void		s_termcaps_identify_input(const unsigned int c,
										t_input_type *input_type,
										size_t *input_size_missing)
{
	size_t	character_size;

	*input_type = MINISHELL__INPUT_TYPE_UNDEFINED;
	*input_size_missing = 0;
	if (ft_isprint(c))
	{
		*input_type = MINISHELL__INPUT_TYPE_PRINT;
	}
	else if (termcaps_isunicode(c, &character_size))
	{
		*input_type = MINISHELL__INPUT_TYPE_UNICODE;
		*input_size_missing = character_size;
	}
	else
	{
		*input_type = MINISHELL__INPUT_TYPE_CAPS;
		if (c == '\x1b')
			*input_size_missing = INPUT_SIZE_MAX - 1;
	}
}

static int		s_termcaps_treat_input(const t_input_type input_type,
										const size_t input_buffer_size,
										const char *input_buffer,
										t_termcaps_context *context)
{
	if (input_type == MINISHELL__INPUT_TYPE_PRINT)
	{
		if (!termcaps_string_to_command_line(input_buffer_size,
										input_buffer, &context->command_line))
		{
			log_error("termcaps_string_to_command_line() failed");
			return (0);
		}
	}
	else if (input_type == MINISHELL__INPUT_TYPE_CAPS)
	{
		caps__exec_func(input_buffer_size, input_buffer, context);
	}
	return (1);
}

#define REVERSE_I_SEARCH					"reverse-i-search: "
#define REVERSE_I_SEARCH_SIZE		(sizeof("reverse-i-search: ") - 1)

static int		s_termcaps_read_loop(t_termcaps_context *context)
{
	size_t			input_buffer_size;
	char			input_buffer[INPUT_SIZE_MAX];
	t_input_type	input_type;
	size_t			input_size_missing;
	t_buffer		history_search;

	while (context->buffer == NULL)
	{
		input_buffer_size = read(context->fd, input_buffer, 1);
		if (input_buffer_size == 0)
			// place it here because we do not want to check for background statuses
		{
			// on each key down event (but only when nothing is typed)
			if (job_background_update_status() > 0)
			{
				caps__delete_line(context->command_line.offset);
				ASSERT(termcaps_display_command_line(context));
				caps__cursor_to_offset(context->command_line.offset,
										context->command_line.size);
			}
			continue ;
		}
		if (input_buffer_size != 1)
		{
			log_error("input_buffer_size %zu input_buffer %.*s", input_buffer_size, (int)sizeof(input_buffer), input_buffer);
		}

		ASSERT(input_buffer_size == 1);
		s_termcaps_identify_input(input_buffer[0],
								&input_type,
								&input_size_missing);
		if (input_buffer_size + input_size_missing > sizeof(input_buffer))
		{
			log_error("Buffer overflow on input_buffer, need %zu but have %zu", input_buffer_size + input_size_missing, sizeof(input_buffer));
			return (0);
		}
		if (input_size_missing)
			input_buffer_size += read(context->fd, input_buffer + 1, input_size_missing);

		if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
		{
			caps__delete_line(context->command_line.offset);
		}
		else if (context->state == STATE_SEARCH_HISTORY)
		{
			caps__delete_line(history_search.size);
		}

		s_termcaps_treat_input(input_type, input_buffer_size, input_buffer,
							   context);

		if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
		{
			ASSERT(termcaps_display_command_line(context));
			caps__cursor_to_offset(context->command_line.offset,
									context->command_line.size);
		}
		else if (context->state == STATE_SEARCH_HISTORY)
		{
			termcaps_history_search(context, &history_search);
			termcaps_write(context->fd, REVERSE_I_SEARCH, REVERSE_I_SEARCH_SIZE);
			termcaps_write(context->fd, history_search.bytes, history_search.size);
		}

	}
	return (1);
}

static int		s_print_first_prompt(t_termcaps_context *context)
{
	int		x;

	ASSERT(caps__cursor_getxy(&x, NULL));
	if (x != 1)
		(void)write(context->fd, "%\n", sizeof("%\n") - 1);
	ASSERT(termcaps_string_to_command_line(context->prompt.size,
										   context->prompt.bytes,
										   &context->command_line));
	ASSERT(termcaps_display_command_line(context));
	return (1);
}

char			*termcaps_read_input(t_termcaps_context *context)
{
	if (context == NULL)
	{
		log_fatal("context %p", (void *)context);
		return (NULL);
	}
	if (!context->is_initialized)
	{
		log_error("context->is_initialized ? %s", context->is_initialized ? "True" : "False");
		return (NULL);
	}

	if (tcsetattr(context->fd, TCSADRAIN, &context->termios_new) != 0)
	{
		log_fatal("tcsetattr() failed to set the terminal fd %d", context->fd);
		return (NULL);
	}
	ASSERT(s_print_first_prompt(context));
	context->state = STATE_REGULAR;

	context->buffer = NULL;
	if (!s_termcaps_read_loop(context))
	{
		log_error("s_termcaps_read_loop() failed");
		context->buffer = NULL;
	}

	if (tcsetattr(context->fd, TCSAFLUSH, &context->termios_old) != 0)
	{
		log_fatal("tcsetattr() failed to restore the terminal");
		return (NULL);
	}
	return (context->buffer);
}
