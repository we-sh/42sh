#include "shell.h"
#include <sys/ioctl.h>
#include <termios.h>

/*
** Display the command line in color
*/

#define ENDL_SIZE (sizeof("\n") - 1)
#define ENDL "\n"

static int	s_display_selection(const t_termcaps_context *context, char *buffer)
{
	size_t		offset_min;
	size_t		offset_max;

	offset_min = MIN(context->command.offset,
		context->selection_offset_start);
	offset_max = MAX(context->command.offset,
		context->selection_offset_start);
	caps__cursor_to_offset(offset_min, context->command.size);
	termcaps_write(context->fd, ANSI_COLOR_LIGHT_BLUE,
		ANSI_COLOR_LIGHT_BLUE_SIZE);
	termcaps_write(context->fd, buffer + offset_min, offset_max - offset_min);
	termcaps_write(context->fd, ANSI_COLOR_RESET, ANSI_COLOR_RESET_SIZE);
	caps__cursor_to_offset(context->command.size, offset_max);
	return (1);
}

static int	s_termcaps_display_control(const t_termcaps_context *context,
										char *buffer, size_t buffer_size)
{
	if (buffer_size % caps__win(WIN_COLUMNS) == 0)
	{
		ft_memcpy(buffer + buffer_size, ENDL, ENDL_SIZE);
		buffer_size += ENDL_SIZE;
	}
	if (buffer_size >= context->prompt.size)
	{
		termcaps_write(context->fd,
				ANSI_COLOR_LIGHT_BLUE, ANSI_COLOR_LIGHT_BLUE_SIZE);
		termcaps_write(context->fd,
				context->prompt.bytes, context->prompt.size);
		termcaps_write(context->fd,
				ANSI_COLOR_RESET, ANSI_COLOR_RESET_SIZE);
		termcaps_write(context->fd,
				buffer + context->prompt.size,
				buffer_size - context->prompt.size);
	}
	else
		termcaps_write(context->fd, buffer, buffer_size);
	if (context->state == STATE_SELECTION)
		s_display_selection(context, buffer);
	return (1);
}

int			termcaps_display_command(const t_termcaps_context *context)
{
	size_t	buffer_size_max;
	size_t	buffer_size;
	char	*buffer;

	buffer_size_max = context->command.size * CHARACTER_SIZE_MAX;
	buffer = (char *)malloc(buffer_size_max + ENDL_SIZE);
	if (!buffer)
	{
		return (0);
	}
	if (!command_to_buffer(&context->command,
											buffer_size_max,
											&buffer_size,
											buffer))
	{
		free(buffer);
		return (0);
	}
	s_termcaps_display_control(context, buffer, buffer_size);
	free(buffer);
	return (1);
}
