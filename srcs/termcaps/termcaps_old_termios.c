#include "shell.h"

/*
** Singelton to store this old_termios_struct
*/

struct termios				termcaps_old_termios(void)
{
	static struct termios	*termios_old = NULL;

	if (termios_old == NULL)
	{
		termios_old = (struct termios *)malloc(sizeof(struct termios));
		if (tcgetattr(0, termios_old) != 0)
			return (*termios_old); // def
	}
	return (*termios_old);
}