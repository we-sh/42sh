#include "shell.h"

/*
** If '-' after the TC_LESSAND, try to close the stdin should produce an error
** after (bad file descriptor).
** If the fd is 0, 1 or 2, this should work.
*/

static int	s_proc(t_proc *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	ret;
	int	fd;

	(void)lexer;
	if (P_TOKEN_CODE(*i) != TC_LESSAND)
		return (ST_PARSER);
	(*i)++;
	if (ft_strcmp(P_TOKEN_CONTENT(*i), "-") == 0)
		fd = -1;
	else
	{
		if ((ret = token_parse_utils_check_char_to_fd(P_TOKEN_CONTENT(*i), &fd)) != ST_OK)
		{
			display_status(ST_PARSER_TOKEN, NULL, P_TOKEN_CONTENT(*i));
			return (ret);
		}
	}
	token_parse_utils_set_proc_fds(target, STDIN_FILENO, fd);
	return (ST_OK);
}

/*
** If jobs, check if the token is TC_LESSAND, if not, call the appropriate
** function, if it is, simply push the command.
*/

static int	s_jobs(t_job *j, t_parser *parser, t_lexer *lexer, int *i)
{
	int	ret;

	if (TOKEN_CODE(*i) != TC_LESSAND)
	{
		ret = lexer->tokens[*i].parse((void *)j, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &(j->command));
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}

/*
** use case : ls no_file | cat <&- return :
** cat: stdin: Bad file descriptor
** ls: sdaf: No such file or directory
** use case : ls no_file | cat <&2 return :
** ls: sdaf: No such file or directory
** 'cat wait for input'
*/

int			token_parse_lessand(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d) `%s'", "TT_REDIR", TOKEN_TYPE(*i), TOKEN_CODE(*i), TOKEN_CONTENT(*i));

	int		ret;

	lexer->tokens[*i].is_redir_checked = 1;
	ret = ST_OK;

	if (parser->mode == F_PARSING_PROCS)
	{
		ret = s_proc((t_proc *)target, parser, lexer, i);
		if (ret != ST_OK)
			((t_proc *)target)->is_valid = 1;
	}
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, parser, lexer, i);
	// epilogue
	(*i)++;
	return (ret);
}
