#include "parser.h"

/*
 ** Open the file pointed by the arg, return -1 on error and display status.
 */

static int	s_open_new_fd(char *f)
{
	int	ret;

	if ((ret = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_printf("%s: %s: %s\n", "42sh", f, i18n_translate(ST_OPEN));
	return (ret);
}

/*
** Try to open a file descriptor according to a string.
** The function will return -ST_PARSER if the string is not "0", "1" or "2".
** Otherwise, the string converted to an int is returned.
*/

static int	s_open_new_fd_int(char *f)
{
	int	ret;

	if ((ft_strisnumeric(f)) == 0)
		return (-ST_PARSER);
	else
	{
		ret = ft_atoi(f);
		if (ret != 0 && ret != 1 && ret != 2)
			return (-ST_PARSER);
	}
	return (ret);
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
** Parse the right part of a redirection (>&2), because it is more complicated
** than the left part.
** Return the file descriptor opened with the redirection, or -ST_PARSER on
** error (assert that ST_PARSER != 1).
** A file descriptor of -1 is not an error, it is considered as a fd closure
** caused by the '-' token (ls 2>&-).
*/

static int	s_parse_right_redir(t_lexer *lexer, int *i)
{
	int	fd_r;

	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(lexer->tokens[*i].content, "-") == 0)
			fd_r = -1;
		else
		{
			if ((fd_r = s_open_new_fd_int(lexer->tokens[*i].content)) == -ST_PARSER)
				return (-ST_PARSER);
		}
	}
	else
	{
		while (lexer->tokens[*i].type == TT_SEPARATOR)
			(*i)++;
		if (lexer->tokens[*i].code != TC_NONE)
			return (-ST_PARSER);
		fd_r = s_open_new_fd(lexer->tokens[*i].content);
	}
	return (fd_r);
}

/*
** Parse the simple right redirection such as 'ls 1>&2'.
** Return ST_OK on success or an error code (from ST_*) on failure.
*/

int			token_parse_chev_right(t_proc *proc, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	st;

	log_trace("entering parsing token %-12s '>'", "TT_REDIR");
	if (lexer->tokens[*i].code == TC_CHEV_RIGHT)
		fd_l = STDOUT_FILENO;
	else
	{
		if ((fd_l = s_open_new_fd_int(lexer->tokens[*i].content)) == -ST_PARSER)
		{
			if ((st = token_parse_none(proc, lexer, i)) != ST_OK)
				return (st);
		}
		(*i)++;
	}
	(*i)++;
	if ((fd_r = s_parse_right_redir(lexer, i)) == -ST_PARSER)
		return (ST_PARSER);
	s_set_proc_fds(proc, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
