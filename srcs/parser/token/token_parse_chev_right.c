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
				display_status(ST_PARSER_TOKEN, NULL, lexer->tokens[*i].content);
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
		if ((ret = token_parse_utils_open_new_fd(p, str, fd, O_WRONLY | O_CREAT | O_TRUNC)) != ST_OK)
			return (ret);
		free(str);
	}
	return (ST_OK);
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
			token_parse_utils_set_proc_fds(p, STDOUT_FILENO, STDERR_FILENO);
			fd_l = STDERR_FILENO;
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
	token_parse_utils_set_proc_fds(p, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
