#include "shell.h"

static int		s_fill_context_buffer(t_internal_context *context, char *buffer)
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
		return (0);
	return (1);
}

static int		s_bufferize_input(t_internal_context *context)
{
	size_t		buffer_size;
	char		buffer[2048];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("list_head__command_line_to_buffer() failed %s\r", "");
		return (0);
	}
	buffer[buffer_size] = '\0';
	if (!s_fill_context_buffer(context, buffer))
	{
		log_error("(s_fill_context_buffer() failed %s", "");
		return (0);
	}
	if (!key__share__command_line_to_history(context))
	{
		log_error("key__share__command_line_to_history() failed %s\r", "");
		return (0);
	}
	context->history.offset = context->history.size;
	if (!termcaps_string_to_command_line(PROMPT_SIZE, PROMPT,
										&context->command_line))
	{
		log_error("minishell__string_to_command_line() failed %s", PROMPT);
		return (0);
	}
	return (1);
}

int				key__send(t_internal_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		if (!termcaps_display_command_line(&context->command_line))
		{
			log_error("minishell__display_command_line() failed %s\r", "");
			return (0);
		}
		caps__print_cap(CAPS__DOWN, 0);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		if (context->command_line.size > PROMPT_SIZE)
		{
			if (!s_bufferize_input(context))
			{
				log_error("s_bufferize_input() failed %s", "");
				return (0);
			}
		}
	}
	return (1);
}
