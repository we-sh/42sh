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

static int	s_parse_right_redir(void *target, t_parser *parser, int *i, int *fd)
{
	int		ret;
	char	*str;

	if (parser->lexer->tokens[*i]->code == TC_AND)
	{
		(*i)++;
		if (ft_strcmp(parser->lexer->tokens[*i]->content, "-") == 0)
			*fd = -1;
		else if ((ret = s_open_new_fd_int(parser->lexer->tokens[*i]->content,
			fd)) != ST_OK)
			return (ret);
	}
	else
	{
		while (parser->lexer->tokens[*i]->type == TT_SEPARATOR
			|| parser->lexer->tokens[*i]->type == TT_INHIBITOR)
		{

			if (parser->mode == F_PARSING_JOBS)
			{
				t_job *j;
				j = (t_job *)target;
				token_parse_utils_push_command(parser->lexer->tokens[*i]->content, &j->command);
			}
			(*i)++;
		}

		str = NULL;
		if ((ret = token_parse_utils_get_full_word(&str, parser->lexer, i)) != ST_OK)
			return (ret);

		if (parser->mode == F_PARSING_JOBS)
		{
			t_job *j;
			j = (t_job *)target;
			token_parse_utils_push_command(str, &j->command);
		}

		if (parser->mode == F_PARSING_PROCS)
		{
			if ((ret = token_parse_utils_open_new_fd((t_proc *)target, str, fd, O_RDONLY)) != ST_OK)
				return (ret);
		}

		free(str);
	}
	return (ST_OK);
}


int			token_parse_less(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int	fd_l;
	int	fd_r;
	int	ret;

	// todo: use parsing mode to customize what this function does

	fd_l = STDIN_FILENO;
	if (lexer->tokens[*i]->code != TC_LESS)
	{
		if ((ret = s_open_new_fd_int(lexer->tokens[*i]->content,
			&fd_l)) != ST_OK)
			return (ret);

		if (parser->mode == F_PARSING_JOBS)
		{
			t_job *j;
			j = (t_job *)target;
			token_parse_utils_push_command(lexer->tokens[*i]->content, &j->command);
		}
		(*i)++;
	}

	if (parser->mode == F_PARSING_JOBS)
	{
		t_job *j;
		j = (t_job *)target;
		token_parse_utils_push_command(lexer->tokens[*i]->content, &j->command);
	}
	(*i)++;

	if ((ret = s_parse_right_redir(target, parser, i, &fd_r)) != ST_OK)
		return (ret);

	if (parser->mode == F_PARSING_PROCS)
		token_parse_utils_set_proc_fds((t_proc *)target, fd_l, fd_r);
	(*i)++;
	return (ST_OK);
}
