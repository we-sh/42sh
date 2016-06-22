#include "parser.h"

static int	s_open_new_fd_int(char *f, int *fd)
{
	if ((ft_strisnumeric(f)) == 0)
		return (ST_PARSER);
	else
	{
		*fd = ft_atoi(f);
		if (*fd != STDIN_FILENO && *fd != STDOUT_FILENO && *fd != STDERR_FILENO)
			return (ST_PARSER);
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
		(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir_proc((t_proc *)target, parser, i, &fd_r)) != ST_OK)
		return (ret);
	token_parse_utils_set_proc_fds(target, fd_l, fd_r);
	(*i)++;
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

int			token_parse_chev_right(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	ret;

	log_trace("entering parsing token %-12s (type: %d) (code: %d)", "TT_REDIR", lexer->tokens[*i].type, lexer->tokens[*i].code);

	if (parser->mode == F_PARSING_PROCS)
		ret = s_token_parse_chev_right_proc((t_proc *)target, parser, lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_token_parse_chev_right_jobs((t_job *)target, parser, lexer, i);
	else
		return (ST_EINVAL); // TODO @jgigault check it
	return (ret);
}
