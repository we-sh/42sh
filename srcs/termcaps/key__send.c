#include "shell.h"

static int 	s_fill_context_buffer(t_internal_context *context, char *buffer)
{
	if (!ft_strcmp(buffer + PROMPT_SIZE, "exit"))
	{
		context->state = STATE_EXIT;
		context->buffer = ft_strdup("exit");
	}
	else
	{
		context->state = STATE_CONTINUE;
		context->buffer = ft_strdup(buffer + PROMPT_SIZE);
	}
	if (!context->buffer)
		return (FALSE);
	return (TRUE);
}

static int 		s_bufferize_input(t_internal_context *context)
{
	size_t		buffer_size;
	char		buffer[2048];

	if (!list_head__command_line_to_buffer(&context->command_line, sizeof(buffer) - 1, &buffer_size, buffer))
		FATAL("list_head__command_line_to_buffer() failed %s\r", "");
	buffer[buffer_size] = '\0';
	if (!s_fill_context_buffer(context, buffer))
		FATAL("(s_fill_context_buffer() failed %s", "");
	if (!key__share__command_line_to_history(context))
		FATAL("key__share__command_line_to_history() failed %s\r", "");
	context->history.offset = context->history.size;
	if (!termcaps_string_to_command_line(PROMPT_SIZE, PROMPT, &context->command_line))
		FATAL("minishell__string_to_command_line() failed %s", PROMPT);
	return (TRUE);
}

int				key__send(t_internal_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		if (!termcaps_display_command_line(&context->command_line))
			FATAL("minishell__display_command_line() failed %s\r", "");
		caps__print_cap(CAPS__DOWN, 0);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		if (context->command_line.size > PROMPT_SIZE)
		{
			if (!s_bufferize_input(context))
				FATAL("s_bufferize_input() failed %s", "");
		}
	}
	return (TRUE);
}
