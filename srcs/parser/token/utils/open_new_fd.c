#include "parser.h"

static int	s_path_is_dir(const char *f)
{
	struct stat	st;
	
	if ((stat(f, &st)) != 0)
		return 0;
	return (S_ISDIR(st.st_mode));
}

int			open_new_fd(t_proc *p, char *f, int *fd)
{
	if ((s_path_is_dir(f)))
	{
		display_status(ST_FISFILE, f, NULL);
		return (ST_FISFILE);
	}
	if ((access(f, F_OK | W_OK)) != 0 )
	{
		display_status(ST_PERMISSION_DENIED, f, NULL);
		return (ST_PERMISSION_DENIED);
	}
	if ((*fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		display_status(ST_OPEN, f, NULL);
		p->is_valid = 0;
	}
	return (ST_OK);
}
