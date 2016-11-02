#include "shell.h"

static int		s_read(t_sh *sh, char **input)
{
	int			gnl_ret;

	gnl_ret = 0;
	if (sh->is_interactive == 1)
	{
		*input = termcaps_read_input(&sh->termcaps_context);
		if (input == NULL)
			return (ST_EXIT);
		if (ft_strcmp(*input, "^C\n") == 0)
			return (ST_CANCEL);
	}
	else
	{
		gnl_ret = get_next_line(sh->fd, input);
		if (gnl_ret < 0)
			return (ST_READ);
		if (gnl_ret == 0)
			return (ST_EXIT);
	}
	return (ST_OK);
}

int				loop_main(t_sh *sh)
{
	char		*input;
	int			ret;

	while (1)
	{
		job_list_clean(1);
		input = NULL;
		if ((ret = s_read(sh, &input)) == ST_EXIT)
			break ;
		else if (ret != ST_OK && ret != ST_CANCEL)
			return (ret);
		else if (ret == ST_OK)
		{
			if ((ret = loop_job_launcher(sh, input, 0)) != ST_OK)
				return (ret);
		}
		if (ret != ST_OK)
			sh->last_exit_status = EXIT_FAILURE;
		ft_strdel(&input);
	}
	return (ST_END_OF_INPUT);
}
