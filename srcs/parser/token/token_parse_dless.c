#include "parser.h"

static int		s_none_check(t_lexer *lexer, int *i)
{
	int			k;

	k = *i + 1;
	while (k < lexer->size && TOKEN_TYPE(k) == TT_SEPARATOR)
		k++;
	if (k >= lexer->size || TOKEN_TYPE(k) != TT_NAME)
	{
		if (lexer->notify == 1)
			display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	return (ST_OK);
}

static int		s_none(t_parser *parser, t_lexer *lexer, int *i)
{
	char		*content;
	int			fd;
	t_redir		*redir;
	int			ret;

	if ((ret = s_none_check(lexer, i)) != ST_OK)
		return (ret);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		return (ret);
	if ((ret = token_parse_utils_heredoc(parser->sh, &fd, content)) != ST_OK)
	{
		free(content);
		return (ret);
	}
	if ((redir = redir_alloc(fd)) == NULL)
	{
		free(content);
		return (ST_MALLOC);
	}
	list_push_back(&redir->list_redir, &parser->sh->redir_head);
	free(content);
	return (ST_OK);
}

static int		s_job(t_job *j, t_lexer *lexer, int *i)
{
	int			ret;
	char		*content;

	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	(*i)++;
	if (token_parse_utils_skip_separators(lexer, i, &j->command) != ST_OK)
		return (ST_MALLOC);
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		return (ret);
	(*i)--;
	if (token_parse_utils_push_command(content, &j->command) != ST_OK)
		return (ST_MALLOC);
	free(content);
	return (ST_OK);
}

static int		s_proc(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	t_list		*pos;
	t_redir		*r;
	char		*content;
	int			ret;

	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		return (ret);
	free(content);
	if ((pos = parser->sh->redir_head.next) == &parser->sh->redir_head)
		return (ST_PARSER);
	r = CONTAINER_OF(pos, t_redir, list_redir);
	p->stdin = r->fd;
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(r);
	(*i)--;
	return (ST_OK);
}

int				token_parse_dless(void *target, t_parser *parser,
					t_lexer *lexer, int *i)
{
	int			ret;

	lexer->tokens[*i]->is_redir_checked = 1;
	if (TOKEN_CODE(*i) != TC_DLESS)
		return (lexer->tokens[*i]->parse(target, parser, lexer, i));
	ret = ST_OK;
	if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target, lexer, i);
	else if (parser->mode == F_PARSING_NONE)
		ret = s_none(parser, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, parser, lexer, i);
	(*i)++;
	return (ret);
}
