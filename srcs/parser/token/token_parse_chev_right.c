#include "parser.h"

static int	s_open_new_fd_int(char *f, int *fd)
{
	int	open_fd;

	if ((ft_strisnumeric(f)) == 0)
		return (ST_PARSER);
	else
	{
		open_fd = ft_atoi(f);
		if (open_fd != STDIN_FILENO && open_fd != STDOUT_FILENO
				&& open_fd != STDERR_FILENO)
			return (ST_PARSER);
		*fd = open_fd;
	}
	return (ST_OK);
}

static int	s_parse_right_redir_proc(t_proc *target, t_parser *parser, int *i, int *fd)
{
	int		ret;
	char	*str;

	if (P_TOKEN_CODE(*i) == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(P_TOKEN_CONTENT(*i), "-") == 0)
		{
			*fd = -1;
		}
		else
		{
			if ((ret = s_open_new_fd_int(P_TOKEN_CONTENT(*i), fd)) != ST_OK)
			{
				display_status(ST_PARSER_TOKEN, NULL, P_TOKEN_CONTENT(*i));
				return (ret);
			}
		}
	}
	else
	{
		while (P_TOKEN_TYPE(*i) == TT_SEPARATOR || P_TOKEN_TYPE(*i) == TT_INHIBITOR)
			(*i)++;
		str = NULL;
		if ((ret = token_parse_utils_get_full_word(&str, parser->lexer, i)) != ST_OK)
			return (ret);
		if ((ret = token_parse_utils_open_new_fd((t_proc *)target, str, fd, O_WRONLY | O_CREAT | O_TRUNC)) != ST_OK)
			return (ret);
		free(str);
	}
	return (ST_OK);

}

static int	s_parse_right_redir_jobs(t_job *target, t_parser *parser, int *i, int *fd)
{
	int		ret;
	char	*str;

	if (P_TOKEN_CODE(*i) == TC_AND)
	{
		token_parse_utils_push_command(P_TOKEN_CONTENT(*i), &(target->command));
		(*i)++;
		if (ft_strcmp(P_TOKEN_CONTENT(*i), "-") == 0)
		{
			token_parse_utils_push_command(P_TOKEN_CONTENT(*i), &(target->command));
			*fd = -1;
		}
	}
	else
	{
		while (P_TOKEN_TYPE(*i) == TT_SEPARATOR || P_TOKEN_TYPE(*i) == TT_INHIBITOR)
		{
			token_parse_utils_push_command(P_TOKEN_CONTENT(*i), &(target->command));
			(*i)++;
		}
		str = NULL;
		if ((ret = token_parse_utils_get_full_word(&str, parser->lexer, i)) != ST_OK)
			return (ret);
		token_parse_utils_push_command(str, &(target->command));
		free(str);
	}
	return (ST_OK);
}

/*
** Parse the token 'right arrow' with a t_proc as target.
** Behavior description :
** - if the token is '>', the left file descriptor is STDOUT_FILENO.
** - else, if the token is '&', redirect both STDOUT_FILENO and STDERR_FILENO.
** - else, if the token is not '&' (eg, 1 for example), check if the given fd is
** one of 0, 1 or 2. If it fails, the token is redirect to token_parse_none.
** - if the token is one of 0, 1 or 2, the left fd is set.
** TODO : set a flag at this step to say that the token was parsed by the arrow.
** The left fd is set, so now, the function parse the right part of the arrow
** to set the right file descriptor.
** The function end by set the proc file descriptors.
*/

static int	s_token_parse_chev_right_proc(t_proc *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int		fd_l;
	int		fd_r;
	int		ret;

	fd_l = STDOUT_FILENO;
	if (TOKEN_CODE(*i) != TC_CHEV_RIGHT)
	{
		if (TOKEN_CODE(*i) == TC_AND)
		{
			token_parse_utils_set_proc_fds(target, STDOUT_FILENO, STDERR_FILENO);
			fd_l = STDERR_FILENO;
		}
		else if ((s_open_new_fd_int(TOKEN_CONTENT(*i), &fd_l)) != ST_OK)
		{
			if ((ret = token_parse_none((void *)target, parser, lexer, i)) != ST_OK)
				return (ret);
		}
		(*i)++; // go on arrow
	}
	(*i)++; // go token next arrow
	if ((ret = s_parse_right_redir_proc((t_proc *)target, parser, i, &fd_r)) != ST_OK)
		return (ret);
	token_parse_utils_set_proc_fds(target, fd_l, fd_r);
	(*i)++; // go on token after right part of the redirection
	return (ST_OK);
}

static int	s_token_parse_chev_right_jobs(t_job *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

	fd_l = STDOUT_FILENO;
	if (TOKEN_CODE(*i) != TC_CHEV_RIGHT)
	{
		if (TOKEN_CODE(*i) != TC_AND && s_open_new_fd_int(TOKEN_CONTENT(*i), &fd_l) != ST_OK)
		{
			if ((ret = token_parse_none((void *)target, parser, lexer, i)) != ST_OK)
				return (ret);
		}
		token_parse_utils_push_command(TOKEN_CONTENT(*i), &(target->command));
		(*i)++;
	}
	token_parse_utils_push_command(TOKEN_CONTENT(*i), &(target->command));
	(*i)++;
	if ((ret = s_parse_right_redir_jobs((t_job *)target, parser, i, &fd_r)) != ST_OK)
		return (ret);
	(*i)++;
	return (ST_OK);
}

/*
** Parse the token 'right arrow'.
** The function applies some modifications on the target (which may be a t_job
** or a t_proc) according to the parser and the lexer.
** Notice that the behavior of the function is different according to target.
*/

int			token_parse_chev_right(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	ret;

	log_trace("entering parsing token %-12s (type: %d) (code: %d) `%s'", "TT_REDIR", TOKEN_TYPE(*i), TOKEN_CODE(*i), TOKEN_CONTENT(*i));

	if (parser->mode == F_PARSING_PROCS)
	{
		// p->is_valid
		ret = s_token_parse_chev_right_proc((t_proc *)target, parser, lexer, i);
	}
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_token_parse_chev_right_jobs((t_job *)target, parser, lexer, i);
	else
	{
		// p->isvalid = -1 (from target)
		// return OK
		return (ST_EINVAL); // TODO @jgigault check it
	}
	return (ret);
}
