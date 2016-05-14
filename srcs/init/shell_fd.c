#include "shell.h"

/*
** This function is called one time at initialization and return the actual tty
** It returns negative value when an error occured
*/

int	shell_fd(void)
{
	static int	*fd = NULL;
	char		*tty_name;

	if (fd == NULL)
	{
		if ((fd = (int *)malloc(sizeof(int))) == NULL)
			return (-ST_MALLOC);
		if ((tty_name = ttyname(STDIN_FILENO)) == NULL)
			return (-ST_TTYNAME);
		if ((*fd = open(tty_name, O_RDWR)) == -1)
			return (-ST_OPEN);
		log_warn("actual tty fd: %d\n", *fd);
		log_info("ttyname: %s, ttyslot: %d\n", tty_name, ttyslot());
	}
	return (*fd);
}
