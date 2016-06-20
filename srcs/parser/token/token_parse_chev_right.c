#include "parser.h"

static int	s_open_new_fd(t_proc *p, char *f, int *fd)
{
	if ((*fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		display_status(ST_OPEN, f, NULL);
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
			return (ST_PARSER);
	}
	return (ST_OK);
}

static int	s_parse_right_redir(t_proc *p, t_lexer *lexer, int *i, int *fd)
{
	int		ret;
	char	*str;

	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(lexer->tokens[*i].content, "-") == 0)
			*fd = -1;
		else
		{
			if ((ret = s_open_new_fd_int(lexer->tokens[*i].content, fd)) != ST_OK)
			{
				display_status(ST_PARSER, lexer->tokens[*i].content, "unexpected member");
				return (ret);
			}
		}
	}
	else
	{
		while (lexer->tokens[*i].type == TT_SEPARATOR || lexer->tokens[*i].type == TT_INHIBITOR)
			(*i)++;
		str = NULL;
		if ((ret = token_parse_utils_get_full_word(&str, lexer, i)) != ST_OK)
			return (ret);
		if ((ret = s_open_new_fd(p, str, fd)) != ST_OK)
			return (ret);
		free(str);
	}
	return (ST_OK);
}

static void	s_set_proc_fds(t_proc *p, int fd_l, int fd_r)
{
	if (!(fd_r == 0 && (fd_l == STDOUT_FILENO || fd_l == STDERR_FILENO)))
	{
		if (fd_l == 0)
			p->stdin = fd_r;
		if (fd_l == 1)
			p->stdout = fd_r;
		if (fd_l == 2)
			p->stderr = fd_r;
	}
}

int			token_parse_chev_right(t_proc *p, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

	fd_l = STDOUT_FILENO;
	if (lexer->tokens[*i].code != TC_CHEV_RIGHT)
	{
		if (lexer->tokens[*i].code == TC_AND)
		{
			s_set_proc_fds(p, 1, 2);
			fd_l = 2;
		}
		else if ((s_open_new_fd_int(lexer->tokens[*i].content, &fd_l)) != ST_OK)
		{
			if ((ret = token_parse_none(p, lexer, i)) != ST_OK)
				return (ret);
		}
		(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir(p, lexer, i, &fd_r)) != ST_OK)
		return (ret);
	s_set_proc_fds(p, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
