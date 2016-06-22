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

static void	s_set_proc_fds(t_proc *p, int fd_l, int fd_r)
{
	if (!(fd_r == 0 && (fd_l == STDOUT_FILENO || fd_l == STDERR_FILENO)))
	{
		if (fd_l == 0)
		{
			if (p->stdin != STDIN_FILENO)
				close(p->stdin);
			p->stdin = fd_r;
		}
		if (fd_l == 1)
		{
			if (p->stdout != STDOUT_FILENO)
				close(p->stdout);
			p->stdout = fd_r;
		}
		if (fd_l == 2)
		{
			if (p->stderr != STDERR_FILENO)
				close(p->stderr);
			p->stderr = fd_r;
		}
	}
}

static int	s_parse_right_redir(t_proc *p, t_lexer *lexer, int *i, int *fd)
{
	if (lexer->tokens[*i].code == TC_AND)
		return (ST_PARSER);
	else
	{
		while (lexer->tokens[*i].type == TT_SEPARATOR)
			(*i)++;
		if (lexer->tokens[*i].code != TC_NONE)
			return (ST_PARSER);
		log_info("%s", lexer->tokens[*i].content);
		token_parse_utils_open_new_fd(p, lexer->tokens[*i].content, fd, O_WRONLY | O_CREAT | O_APPEND);
		log_info("%d", *fd);
	}
	return (ST_OK);
}

int			token_parse_dbl_chev_right(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

	log_error("todo !!!");
	return (ST_PARSER);

	// todo: use parsing mode to customize what this function does
	t_proc	*p;
	p = (t_proc *)target;
	(void)parser;

	log_trace("entering parsing token %-12s '>>'", "TT_REDIR");
	fd_l = STDOUT_FILENO;
	if (lexer->tokens[*i].code != TC_DBL_CHEV_RIGHT)
	{
		if ((ret = s_open_new_fd_int(lexer->tokens[*i].content, &fd_l)) != ST_OK)
			return (ret);
		(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir(p, lexer, i, &fd_r)) != ST_OK)
		return (ret);
	s_set_proc_fds(p, fd_l, fd_r);
	(*i)++;
	return (0);
}
