#include "parser.h"

/*
** Case : cat < README
*/

static int	s_open_new_fd(t_proc *p, char *f, int *fd)
{
	if ((*fd = open(f, O_RDONLY)) < 0)
	{
		display_status(ST_ENOENT, f, NULL);
		p->is_valid = 0;
	}
	return (ST_OK);
}

static int	s_open_new_fd_int(char *f, int *fd)
{
	if ((ft_strisnumeric(f)) == 0)
		return (ST_PARSER);
	else
	{
		*fd = ft_atoi(f);
		if (*fd != STDIN_FILENO && *fd != STDOUT_FILENO && *fd != STDERR_FILENO)
		{
			log_error("bad file descriptor");
			return (ST_PARSER);
		}
	}
	return (ST_OK);
}

static int	s_parse_right_redir(t_proc *p, t_lexer *lexer, int *i, int *fd)
{
	int		ret;

	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(lexer->tokens[*i].content, "-") == 0)
			*fd = -1;
		else
		{
			if ((ret = s_open_new_fd_int(lexer->tokens[*i].content,
				fd)) != ST_OK)
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

int			token_parse_chev_left(t_proc *proc, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

	log_trace("entering parsing token %-12s '<'", "TT_REDIR");
	// parse left part of the redirection
	if (lexer->tokens[*i].code == TC_CHEV_LEFT)
		fd_l = STDIN_FILENO;
	else
	{
		if ((ret = s_open_new_fd_int(lexer->tokens[*i].content,
			&fd_l)) != ST_OK)
			return (ret);
		(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir(proc, lexer, i, &fd_r)) != ST_OK)
		return (ret);
	s_set_proc_fds(proc, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
