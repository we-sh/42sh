#include "shell.h"

static t_internal_context context = {
	.state = STATE_REGULAR,

	.buffer = NULL,

	.command_line = {
		.size = 0,
		.list = {
			.next = &context.command_line.list,
			.prev = &context.command_line.list
		},
		.offset = 0
	},

	.copy = {
		.size = 0,
		.list = {
			.next = &context.copy.list,
			.prev = &context.copy.list
		},
		.offset = 0
	},
	.selection_offset_start = 0,
	.selection_offset_end = 0,

	.history = {
		.size = 0,
		.list = {
			.next = &context.history.list,
			.prev = &context.history.list
		},
		.offset = 0
	},
};

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
										t_internal_context *context)
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

static int		s_print_first_prompt(void)
{
	if (context.state == STATE_REGULAR)
	{
		ASSERT(termcaps_string_to_command_line(PROMPT_SIZE,
												PROMPT, &context.command_line));
		ASSERT(termcaps_display_command_line(&context.command_line));
	}
	else if (context.state == STATE_CONTINUE)
	{
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		ASSERT(termcaps_display_command_line(&context.command_line));
	}
	return (1);
}

static int		s_termcaps_read_loop(const int fd)
{
	size_t			input_buffer_size;
	char			input_buffer[INPUT_SIZE_MAX];
	t_input_type	input_type;
	size_t			input_size_missing;

	while (context.state != STATE_EXIT && context.state != STATE_CONTINUE)
	{
		input_buffer_size = read(fd, input_buffer, 1);
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
			input_buffer_size += read(fd, input_buffer + 1, input_size_missing);
		caps__delete_line(context.command_line.offset);
		s_termcaps_treat_input(input_type, input_buffer_size, input_buffer,
								&context);
		if (context.state == STATE_REGULAR || context.state == STATE_SELECTION)
		{
			ASSERT(termcaps_display_command_line(&context.command_line));
			caps__cursor_to_offset(context.command_line.offset,
									context.command_line.size);
		}
	}
	return (1);
}

char			*termcaps_read_input(const int fd)
{
	ASSERT(s_print_first_prompt() != 0);
	context.state = STATE_REGULAR;
	context.buffer = NULL;
	if (!s_termcaps_read_loop(fd))
	{
		context.buffer = NULL;
		context.state = STATE_EXIT;
	}
	if (context.state == STATE_EXIT)
	{
		list_head__command_line_destroy(&context.copy);
		list_head__command_line_destroy(&context.command_line);
		list_head__history_destroy(&context.history);
	}
	return (context.buffer);
}
