#include "parser.h"

/*
 ** Open the file pointed by the arg,display status message on error.
 */

static int	s_open_new_fd(t_proc *p, char *f, int *fd)
{
	if ((*fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		display_status(ST_OPEN, f, NULL);
		p->is_valid = 0;
	}
	return (ST_OK);
}

/*
** Try to extract a file descriptor according to a string. It will not open
** it because it is STDIN_FILENO, STDOUT_FILENO or STDERR_FILENO.
** The function will return ST_PARSER if the string is not "0", "1" or "2".
** Otherwise, the string converted to an int is set in the fd argument.
*/

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

/*
** Parse the right part of a redirection (>&2), because it is more complicated
** than the left part.
** Return the file descriptor opened with the redirection, or -ST_PARSER on
** error (assert that ST_PARSER != 1).
** A file descriptor of -1 is not an error, it is considered as a fd closure
** caused by the '-' token (ls 2>&-).
*/

static int	s_parse_right_redir(t_proc *p, t_lexer *lexer, int *i, int *fd)
{
	int	ret;

	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(lexer->tokens[*i].content, "-") == 0)
			*fd = -1;
		else
		{
			if ((ret = s_open_new_fd_int(lexer->tokens[*i].content, fd)) != ST_OK)
				return (ret);
		}
	}
	else
	{
		while (lexer->tokens[*i].type == TT_SEPARATOR)
			(*i)++;
		if (lexer->tokens[*i].code != TC_NONE)
			return (ST_PARSER);
		if ((ret = s_open_new_fd(p, lexer->tokens[*i].content, fd)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

/*
** Update the proc after the opening of all the redirections.
*/

static void	s_set_proc_fds(t_proc *proc, int fd_l, int fd_r)
{
	if (!(fd_r == 0 && (fd_l == STDOUT_FILENO || fd_l == STDERR_FILENO)))
	{
		if (fd_l == 0)
			proc->stdin = fd_r;
		if (fd_l == 1)
			proc->stdout = fd_r;
		if (fd_l == 2)
			proc->stderr = fd_r;
	}
}

/*
** Parse the simple right redirection such as 'ls 1>&2'.
** Return ST_OK on success or an error code (from ST_*) on failure.
*/

int			token_parse_chev_right(t_proc *proc, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

	log_trace("entering parsing token %-12s '>'", "TT_REDIR");
	if (lexer->tokens[*i].code == TC_CHEV_RIGHT)
		fd_l = STDOUT_FILENO;
	else
	{
		if ((ret = s_open_new_fd_int(lexer->tokens[*i].content, &fd_l)) != ST_OK)
		{
			if ((ret = token_parse_none(proc, lexer, i)) != ST_OK)
				return (ret);
		}
		(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir(proc, lexer, i, &fd_r)) != ST_OK)
		return (ret);
	s_set_proc_fds(proc, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
