#include "parser.h"

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
	int		ret;
	char	*path;

	token_parse_utils_skip_separators(lexer, i, NULL);
	path = NULL;
	if ((ret = token_parse_utils_get_full_word(&path,
												lexer, i)) != ST_OK)
		return (ret);
	log_error(path);
	if ((ret = token_parse_utils_open_new_fd(p, path, fd,
								O_WRONLY | O_CREAT | O_APPEND)) != ST_OK)
		return (ret);
	free(path);
	(*i)--;
	return (ST_OK);
}

static int	s_jobs(t_job *j, t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	if (TOKEN_CODE(*i) != TC_DGREAT)
	{
		ret = lexer->tokens[*i]->parse((void *)j, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	int		fd_r;
	int		fd_l;
	int		ret;

	fd_l = STDOUT_FILENO;
	if (TOKEN_CODE(*i) != TC_DGREAT)
	{
		ret = token_parse_utils_check_char_to_fd(TOKEN_CONTENT(*i), &fd_l);
		if (ret != ST_OK)
		{
			ret = lexer->tokens[*i]->parse((void *)p, parser, lexer, i);
			if (ret != ST_OK)
				return (ret);
		}
		else
			(*i)++;
	}
	(*i)++;
	if ((ret = s_parse_right_redir(p, lexer, i, &fd_r)) != ST_OK)
		return (ret);
	s_set_proc_fds(p, fd_l, fd_r);
	return (ST_OK);
}

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	if (TOKEN_CODE(*i) != TC_DGREAT)
		(*i)++;
	content = TOKEN_CONTENT(*i);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	return (ST_OK);
}

int			token_parse_dgreat(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	lexer->tokens[*i]->is_redir_checked = 1;
	ret = ST_OK;
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, parser, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, parser, lexer, i);
	(*i)++;
	return (ret);
}
