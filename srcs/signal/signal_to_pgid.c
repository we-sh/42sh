#include "shell.h"

static void	s_sigtstp(int sig)
{
	static int	gpid = 0;

	if (sig < 0)
		gpid = sig;
	else if (sig != 0)
	{
		if (gpid < 0)
		{
			kill(gpid, SIGTSTP);
		}
	}
}

static void	s_sigint(int sig)
{
	static int	gpid = 0;

	if (sig < 0)
		gpid = sig;
	else if (sig != 0)
	{
		if (gpid < 0)
		{
			kill(gpid, SIGINT);
		}
	}
}

static void	s_sigquit(int sig)
{
	static int	gpid = 0;

	if (sig < 0)
		gpid = sig;
	else if (sig != 0)
	{
		if (gpid < 0)
		{
			kill(gpid, SIGQUIT);
		}
	}
}

int			signal_to_pgid(int pgid)
{
	s_sigint(-pgid);
	s_sigtstp(-pgid);
	s_sigquit(-pgid);
	if (pgid != 0)
	{
		if (signal(SIGINT, s_sigint) == SIG_ERR)
			return (ST_SIGNAL);
		if (signal(SIGTSTP, s_sigtstp) == SIG_ERR)
			return (ST_SIGNAL);
		if (signal(SIGQUIT, s_sigquit) == SIG_ERR)
			return (ST_SIGNAL);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			return (ST_SIGNAL);
		if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
			return (ST_SIGNAL);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (ST_SIGNAL);
	}
	return (ST_OK);
}
