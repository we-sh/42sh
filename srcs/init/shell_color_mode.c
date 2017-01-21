#include "shell.h"

int	shell_color_mode(int color_mode)
{
	static int current_color_mode = 0;

	if (color_mode != -1)
		current_color_mode = color_mode;
	return (current_color_mode);
}
