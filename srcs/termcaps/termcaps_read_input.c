#include "shell.h"
#include <sys/ioctl.h>

int					s_check_cursor_pos(t_termcaps_context *context)
{
	int		input_queue_byte_count;
	int		x;

	if (context->option == OPTION_NONE)
	{
		if (ioctl(context->fd, FIONREAD, &input_queue_byte_count) != -1)
		{
			if (input_queue_byte_count == 0)
			{
				ASSERT(caps__cursor_getxy(&x, NULL));
				if (x != 1)
					termcaps_write(context->fd, "%\n", sizeof("%\n") - 1);
			}
		}
	}
	return (1);
}

int					s_set_new_prompt(t_termcaps_context *context)
{
	char		*tmp;

	free(context->prompt.bytes);
	if (!(tmp = env_get(context->sh->envp, "PS1")))
	{
		tmp = shell_set_prompt(context->sh);
		context->prompt.size = ft_strlen(tmp);
		context->prompt.bytes = tmp;
	}
	else
	{
		context->prompt.size = ft_strlen(tmp);
		context->prompt.bytes = ft_strdup(tmp);
	}
	return (ST_OK);
}

char				*termcaps_read_input(t_termcaps_context *context)
{
	size_t			input_buffer_size;
	size_t			input_size_missing;

	input_buffer_size = 0;
	input_size_missing = 0;
	ASSERT(context != NULL && context->is_initialized);
	ASSERT(!tcsetattr(context->fd, TCSADRAIN, &context->termios_new));
	ASSERT(s_check_cursor_pos(context));
	if (context->option == OPTION_NONE)
		s_set_new_prompt(context);
	ASSERT(command_add_string(context->prompt.size,
											context->prompt.bytes,
											&context->command));
	ASSERT(termcaps_display_command(context));
	context->state = STATE_REGULAR;
	context->buffer = NULL;
	ASSERT(termcaps_read_loop(context, input_buffer_size,
		input_size_missing));
	ASSERT(!tcsetattr(context->fd, TCSANOW, &context->termios_old));
	return (context->buffer);
}
