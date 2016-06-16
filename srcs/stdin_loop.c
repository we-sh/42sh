#include "shell.h"

int					stdin_loop(t_sh *sh)
{
	char				*input;
	int					ret;
	bool				end_of_file;

	end_of_file = 1;
	input = NULL;
	while (1)
	{
		if (sh->is_interactive == true)
			input = termcaps_read_input(&sh->termcaps_context);
		else
			end_of_file = get_next_line(sh->fd, &input);
		if (input == NULL || end_of_file == 0)
		{
			log_info("termcaps_read_input() returned NULL");
			break ;
		}
		// FIX
		if ((ret = parser(sh, input)) < 0)
			ret = 1;
		if (ret != ST_OK)
		{
			if (ret == ST_EXIT)
				return (ST_OK);
			display_status(ret, NULL, NULL);
		}
		ft_strdel(&input);
		input = NULL;
	}
	return (ST_END_OF_INPUT);
}
