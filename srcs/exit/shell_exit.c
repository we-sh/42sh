#include "shell.h"

/*
** This function exits the Shell and does:
** - display a message error if `status` is different from ST_OK
** - (TODO) set the termios structure to its original value
*/

void	shell_exit(int status)
{
  struct termios  *ter;

	if (status > ST_OK)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(i18n_translate(status), STDERR_FILENO);
	}
  ter = termcaps_old_termios();
  if (ter == NULL)
  {
    log_error("termcaps_termios_old() failed, restart your terminal");
    exit(status);
  }
  if (tcsetattr(shell_fd(), TCSADRAIN, ter) == -1)
    log_error("tcsetattr() failed to restore the terminal");
	exit(status);
}
