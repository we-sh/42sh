#include "parser.h"

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
	char	*str;

	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(lexer->tokens[*i].content, "-") == 0)
			*fd = -1;
		else if ((ret = s_open_new_fd_int(lexer->tokens[*i].content,
			fd)) != ST_OK)
			return (ret);
	}
	else
	{
		while (lexer->tokens[*i].type == TT_SEPARATOR
			|| lexer->tokens[*i].type == TT_INHIBITOR)
			(*i)++;
		str = NULL;
		if ((ret = token_parse_utils_get_full_word(&str, lexer, i)) != ST_OK)
			return (ret);
		if ((ret = token_parse_utils_open_new_fd(p, str, fd, O_RDONLY)) != ST_OK)
			return (ret);
		free(str);
	}
	return (ST_OK);
}


int			token_parse_chev_left(t_proc *proc, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

		fd_l = STDIN_FILENO;
	if (lexer->tokens[*i].code != TC_CHEV_LEFT)
	{
		if ((ret = s_open_new_fd_int(lexer->tokens[*i].content,
			&fd_l)) != ST_OK)
			return (ret);
		(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir(proc, lexer, i, &fd_r)) != ST_OK)
		return (ret);
	token_parse_utils_set_proc_fds(proc, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
