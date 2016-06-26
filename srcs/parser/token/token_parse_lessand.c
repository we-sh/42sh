#include "shell.h"

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	content = TOKEN_CONTENT(*i);
	(*i)++;
	if (*i >= lexer->size || (TOKEN_CONTENT(*i)[0] != '-'
								&& ft_strisnumeric(TOKEN_CONTENT(*i)) == 0))
	{
		display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	(*i)--;
	return (ST_OK);
}

static int	s_proc(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;
	int		fd;
	char	*content;

	ret = ST_OK;
	(*i)++;
	if (TOKEN_CONTENT(*i)[0] == '-')
	{
		fd = -1;
		ret = token_parse_utils_gen_token_after_dash(p, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	else
	{
		content = TOKEN_CONTENT(*i);
		if ((ret = token_parse_utils_check_char_to_fd(content, &fd)) != ST_OK)
		{
			display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
			return (ret);
		}
	}
	token_parse_utils_set_proc_fds(p, STDIN_FILENO, fd);
	return (ST_OK);
}

static int	s_jobs(t_job *j, t_lexer *lexer, int *i)
{
	int		ret;

	log_error(TOKEN_CONTENT(*i));
	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}

int			token_parse_lessand(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d) `%s'", "TT_REDIR", TOKEN_TYPE(*i), TOKEN_CODE(*i), TOKEN_CONTENT(*i));

	int		ret;

	lexer->tokens[*i]->is_redir_checked = 1;
	ret = ST_OK;
	if (TOKEN_CODE(*i) != TC_LESSAND)
		return (lexer->tokens[*i]->parse(target, parser, lexer, i));
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
	{
		ret = s_proc((t_proc *)target, parser, lexer, i);
		if (ret != ST_OK)
			((t_proc *)target)->is_valid = -1;
	}
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, lexer, i);
	(*i)++;
	return (ret);
}
