#include "parser.h"

static int	s_fill_command(t_proc *p, char *content)
{
	char	*tmp;

	if (!(p->command))
		p->command = ft_strdup(content);
	else
	{
		tmp = ft_strjoin(p->command, content);
		free(p->command);
		p->command = tmp;
	}
	if (p->command == NULL)
		return (ST_MALLOC);
	return (ST_OK);
}

int	token_parse_none(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d)", "TT_NONE", lexer->tokens[*i].type, lexer->tokens[*i].code);

	char	*content;
	int		ret;
	int		is_inhibited;

	// todo: should be catch in parsing mode F_PARSING_NONE
	if (lexer->tokens[*i].type == TT_ERROR)
		return (ST_PARSER);

	if ((*i) + 1 < lexer->size && TOKEN_TYPE((*i) + 1) == TT_REDIR)
	{
		return (token_parse_chev_right(target, parser, lexer, i));
	}
	// todo: use parsing mode to customize what this function does
	if (parser->mode == F_PARSING_JOBS)
	{
		t_job *j;
		j = (t_job *)target;
		token_parse_utils_push_command(lexer->tokens[*i].content, &j->command);

		int inhibitor;
		inhibitor = (*i > 0 && lexer->tokens[*i].type == TT_INHIBITOR) ? lexer->tokens[*i].code : 0;

		while (inhibitor != 0 && *i + 1 < lexer->size && lexer->tokens[*i + 1].code != inhibitor)
		{
			token_parse_utils_push_command(lexer->tokens[*i + 1].content, &j->command);
			(*i)++;
		}

	}
	else if (parser->mode == F_PARSING_PROCS)
	{

		t_proc	*p;
		p = (t_proc *)target;
		(void)parser;

		is_inhibited = *i == 0 ? 0 : lexer->tokens[*i - 1].type == TT_INHIBITOR;
		if ((ret = s_fill_command(p, lexer->tokens[*i].content)) != ST_OK)
			return (ret);
		if (!(lexer->tokens[*i].type == TT_NAME
			&& lexer->tokens[*i].code == TC_NONE))
			return (ST_OK);
		if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
			return (ret);
		if ((ret = expand(lexer->sh, p, content, is_inhibited)) != ST_OK)
		{
			log_fatal("failed to push `%s` intro p->argv", lexer->tokens[*i].content);
			return (ret);
		}
	}
	return (0);
}
