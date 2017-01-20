#include "shell.h"

void				path_set_struct_display(t_display_h *display)
{
	display->i = 0;
	display->max = 0;
	display->folders_nbr = 0;
	display->total_binaries = 0;
}
