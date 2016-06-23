#include "parser.h"

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
			if ((ret = token_parse_utils_check_char_to_fd(P_TOKEN_CONTENT(*i), fd)) != ST_OK)
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

static int	s_great_parse_proc(t_proc *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int		fd_l;
	int		fd_r;
	int		ret;

	fd_l = STDOUT_FILENO;
	if (TOKEN_CODE(*i) != TC_GREAT)
	{
		if (TOKEN_CODE(*i) == TC_AND)
		{
			token_parse_utils_set_proc_fds(target, STDOUT_FILENO, STDERR_FILENO);
			fd_l = STDERR_FILENO;
		}
		else if ((token_parse_utils_check_char_to_fd(TOKEN_CONTENT(*i), &fd_l)) != ST_OK)
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

/*
** If the left token is not a great, it push the token into the command.
** If the token is not a and, it call token_parse_none.
*/

static int	s_great_parse_jobs(t_job *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	ret;

	if (TOKEN_CODE(*i) != TC_GREAT)
	{
			if ((ret = token_parse_none((void *)target, parser, lexer, i)) != ST_OK)
				return (ret);
	}
	token_parse_utils_push_command(TOKEN_CONTENT(*i), &(target->command));
	return (ST_OK);
}

/*
** Parse the token 'right arrow'.
** The function applies some modifications on the target (which may be a t_job
** or a t_proc) according to the parser and the lexer.
** Notice that the behavior of the function is different according to target.
*/

int			token_parse_great(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d) `%s'", "TT_REDIR", TOKEN_TYPE(*i), TOKEN_CODE(*i), TOKEN_CONTENT(*i));

	int	ret;

	// setup
	// @jigault : where to use it? In TC_NONE?
	lexer->tokens[*i].is_redir_checked = 1;
	ret = ST_OK;

	if (parser->mode == F_PARSING_PROCS)
	{
		ret = s_great_parse_proc((t_proc *)target, parser, lexer, i);
		if (ret != ST_OK)
			((t_proc *)target)->is_valid = 1;
	}
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_great_parse_jobs((t_job *)target, parser, lexer, i);

	// epilogue
	(*i)++;
	return (ret);
}
