#include "shell.h"

static int		s_read_with_gnl_return(t_sh *sh, char **input)
{
	if (*input && parser(sh, *input, F_PARSING_TERMCAPS, NULL) != ST_OK)
		return (ST_PARSER);
	return (*input == NULL ? ST_EXIT : ST_OK);
}

static int		s_read_with_gnl(t_sh *sh, char **input)
{
	int			ret;
	char		*input_tmp;
	char		*tmp;

	while (1)
	{
		input_tmp = NULL;
		ret = get_next_line(sh->fd, &input_tmp);
		if (ret < 0)
			return (ST_READ);
		if (ret == 0)
			return (s_read_with_gnl_return(sh, input));
		if (*input != NULL)
		{
			tmp = *input;
			*input = ft_strjoin(*input, input_tmp);
			free(tmp);
		}
		else
			*input = ft_strdup(input_tmp);
		free(input_tmp);
		if (parser(sh, *input, F_PARSING_TERMCAPS, NULL) == ST_OK)
			break ;
	}
	return (ST_OK);
}

static int		s_read(t_sh *sh, char **input)
{
	int			ret;

	ret = 0;
	if (sh->is_interactive == 1)
	{
		*input = termcaps_read_input(&sh->termcaps_context);
		if (input == NULL)
			return (ST_EXIT);
		if (ft_strcmp(*input, "^C\n") == 0)
			return (ST_CANCEL);
	}
	else
		return (s_read_with_gnl(sh, input));
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
		ret = s_read(sh, &input);
		if (ret == ST_EXIT)
			break ;
		else if (ret != ST_OK && ret != ST_CANCEL)
			return (ret);
		else if (ret == ST_OK)
		{
			if ((ret = loop_job_launcher(sh, input)) != ST_OK)
				return (ret);
		}
		if (ret != ST_OK)
			sh->last_exit_status = EXIT_FAILURE;
		ft_strdel(&input);
	}
	return (ST_END_OF_INPUT);
}
