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

static int		s_check_job_status(t_termcaps_context *context)
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

#define REVERSE_I_SEARCH					"reverse-i-search"
#define REVERSE_I_SEARCH_SIZE		(sizeof("reverse-i-search") - 1)

static void		s_delete_line(t_termcaps_context *context,
							const t_buffer history_search)
{
	if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
	{
		caps__delete_line(context->command_line.offset);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		caps__delete_line(history_search.size +
						REVERSE_I_SEARCH_SIZE +
						sizeof(" '' : ") - 1);
	}
}

static int		s_display_line(t_termcaps_context *context, t_buffer *history_search)
{
	char		buffer[2048];
	size_t		buffer_size;

	if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
	{
		ASSERT(termcaps_display_command_line(context));
		caps__cursor_to_offset(context->command_line.offset,
							context->command_line.size);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		termcaps_write(context->fd, REVERSE_I_SEARCH, REVERSE_I_SEARCH_SIZE);
		if (list_head__command_line_to_buffer(&context->command_line,
								sizeof(buffer), &buffer_size, buffer))
		{
			termcaps_write(context->fd, " '", sizeof(" '") - 1);
			termcaps_write(context->fd, buffer + context->prompt.size,
										buffer_size - context->prompt.size);
			termcaps_write(context->fd, "' : ", sizeof("' : ") - 1);
		}
		if (termcaps_history_search(context, history_search))
			termcaps_write(context->fd,
						history_search->bytes, history_search->size);
	}
	return (1);
}

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
			s_check_job_status(context);
		else if (input_buffer_size == 1)
		{
			s_termcaps_identify_input(input_buffer[0], &input_type,
										&input_size_missing);
			ASSERT(input_buffer_size + input_size_missing <= sizeof(input_buffer));
			if (input_size_missing)
				input_buffer_size += read(context->fd, input_buffer + 1, input_size_missing);
			s_delete_line(context, history_search);
			s_termcaps_treat_input(input_type, input_buffer_size, input_buffer,
									context);
			ASSERT(s_display_line(context, &history_search));
			log_success("history offset %zu", context->history.offset);
		}
	}
	return (1);
}

char			*termcaps_read_input(t_termcaps_context *context)
{
	int		x;

	ASSERT(context != NULL && context->is_initialized);
	ASSERT(!tcsetattr(context->fd, TCSADRAIN, &context->termios_new));
	ASSERT(caps__cursor_getxy(&x, NULL));
	if (x != 1)
		termcaps_write(context->fd, "%\n", sizeof("%\n") - 1);
	ASSERT(termcaps_string_to_command_line(context->prompt.size,
										   context->prompt.bytes,
										   &context->command_line));
	ASSERT(termcaps_display_command_line(context));
	context->state = STATE_REGULAR;
	context->buffer = NULL;
	ASSERT(s_termcaps_read_loop(context));
	ASSERT(!tcsetattr(context->fd, TCSAFLUSH, &context->termios_old));
	return (context->buffer);
}
