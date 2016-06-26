#include "parser.h"

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	content = TOKEN_CONTENT(*i);
	log_error(content);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	return (ST_OK);
}

static int	s_job(t_job *j, t_lexer *lexer, int *i)
{
	int		ret;

	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_lexer *lexer, int *i)
{
	int		ret;
	int		fd_r;
	char	*path;

	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	path = NULL;
	if ((ret = token_parse_utils_get_full_word(&path, lexer, i)) != ST_OK)
		return (ret);
	ret = ST_OK;
	if ((ret = token_parse_utils_open_new_fd(p, path, &fd_r, O_RDONLY)) != ST_OK)
		return (ret);
	free(path);
	token_parse_utils_set_proc_fds(p, STDIN_FILENO, fd_r);
	return (ST_OK);
}

int			token_parse_less(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d) (content: `%s')", "TT_REDIR", TOKEN_TYPE(*i), TOKEN_CODE(*i), TOKEN_CONTENT(*i));

	int		ret;

	lexer->tokens[*i]->is_redir_checked = 1;
	ret = ST_OK;
	if (TOKEN_CODE(*i) != TC_LESS)
		return (lexer->tokens[*i]->parse(target, parser, lexer, i));
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, lexer, i);
	(*i)++;
	return (ret);
}
