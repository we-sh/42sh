#include "parser.h"

/*
 ** Open the file pointed by the arg, return -1 on error and display status.
 */

static int	s_open_new_fd(char *f)
{
	int	ret;

	if ((ret = open(f, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
		ft_printf("%s: %s: %s\n", "42sh", f, i18n_translate(ST_OPEN));
	return (ret);
}

static int	s_open_new_fd_int(char *f)
{
	int	ret;

	if ((ft_strisnumeric(f)) == 0)
		return (ST_PARSER);
	else
	{
		ret = ft_atoi(f);
		if (ret != 0 && ret != 1 && ret != 2)
			log_error("bad file descriptor");
	}
	return (ret);
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

static int	s_parse_right_redir(t_lexer *lexer, int *i)
{
	int	fd_r;

	if (lexer->tokens[*i].code == TC_AND)
		return (ST_PARSER);
	else
	{
		while (lexer->tokens[*i].type == TT_SEPARATOR)
			(*i)++;
		if (lexer->tokens[*i].code != TC_NONE)
			return (ST_PARSER);
		fd_r = s_open_new_fd(lexer->tokens[*i].content);
	}
	return (fd_r);
}

int			token_parse_dbl_chev_right(t_proc *proc, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;

	log_trace("entering parsing token %-12s '>>'", "TT_REDIR");
	// parse left part of the redirection
	if (lexer->tokens[*i].code == TC_DBL_CHEV_RIGHT)
		fd_l = STDOUT_FILENO;
	else
	{
		if ((fd_l = s_open_new_fd_int(lexer->tokens[*i].content)) == ST_PARSER)
			return (ST_PARSER);
		(*i)++;
	}
	(*i)++;
	if ((fd_r = s_parse_right_redir(lexer, i)) == ST_PARSER)
		return (ST_PARSER);
	s_set_proc_fds(proc, fd_l, fd_r);
	(*i)++;
	return (0);
}
