#include "shell.h"
#include <sys/ioctl.h>
#include <termios.h>

/*
**	 A deplacer
*/

#ifdef __linux__
# define SELECTBLANC "\e]12;white\a"
# define SELECTBLEU "\e]12;blue\a"
#else
# define SELECTBLANC "\033]Plffffff\033\\"
# define SELECTBLEU "\033]Pl4040ff\033\\"
#endif

#define ANSI_COLOR_RESET_SIZE (sizeof("\033[0m") - 1)
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_LIGHT_BLUE_SIZE (sizeof("\033[94m") - 1)
#define ANSI_COLOR_LIGHT_BLUE "\033[94m"

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

/*
** Display the command line in color
*/

#define ENDL_SIZE (sizeof("\n") - 1)
#define ENDL "\n"

static int	s_display_selection(const t_termcaps_context *context, char *buffer)
{
	size_t		offset_min;
	size_t		offset_max;

	offset_min = MIN(context->command_line.offset,
		context->selection_offset_start);
	offset_max = MAX(context->command_line.offset,
		context->selection_offset_start);
	caps__cursor_to_offset(offset_min, context->command_line.size);
	termcaps_write(context->fd, ANSI_COLOR_LIGHT_BLUE,
		ANSI_COLOR_LIGHT_BLUE_SIZE);
	termcaps_write(context->fd, buffer + offset_min, offset_max - offset_min);
	termcaps_write(context->fd, ANSI_COLOR_RESET, ANSI_COLOR_RESET_SIZE);
	caps__cursor_to_offset(context->command_line.size, offset_max);
	return (ST_OK);
}

static int	s_termcaps_display_control(const t_termcaps_context *context,
										char *buffer, size_t buffer_size)
{
	if (buffer_size % caps__win(WIN_COLUMNS) == 0)
	{
		ft_memcpy(buffer + buffer_size, ENDL, ENDL_SIZE);
		buffer_size += ENDL_SIZE;
	}
	ASSERT(termcaps_write(context->fd, buffer, buffer_size));
	if (context->state == STATE_SELECTION)
		s_display_selection(context, buffer);
	free(buffer);
	return (ST_OK);
}

int			termcaps_display_command_line(const t_termcaps_context *context)
{
	size_t	buffer_size_max;
	size_t	buffer_size;
	char	*buffer;

	buffer_size_max = context->command_line.size * CHARACTER_SIZE_MAX;
	buffer = malloc(buffer_size_max);
	if (!buffer)
	{
		log_error("malloc() failed command_line->size %zu", buffer_size_max);
		return (0);
	}
	if (!list_head__command_line_to_buffer(&context->command_line,
											buffer_size_max - ENDL_SIZE,
											&buffer_size,
											buffer))
	{
		log_error("list_head__command_line_to_buffer()");
		free(buffer);
		return (0);
	}
	s_termcaps_display_control(context, buffer, buffer_size);
	return (1);
}
