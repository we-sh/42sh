#include "parser.h"

static int	s_proc(t_proc *p, t_lexer *lexer, int *i)
{
	char	*content;
	int		is_inhibited;
	int		ret;

	is_inhibited = *i == 0 ? 0 : TOKEN_TYPE(*i - 1) == TT_INHIBITOR;
	/*if ((ret = s_fill_command(p, lexer->tokens[*i].content)) != ST_OK)
		return (ret);
	if (!(lexer->tokens[*i].type == TT_NAME
		&& lexer->tokens[*i].code == TC_NONE))
		return (ST_PARSER);*/
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		return (ret);
	if ((ret = expand(lexer->sh, p, content, is_inhibited)) != ST_OK)
	{
		log_fatal("failed to push `%s` intro p->argv", TOKEN_CONTENT(*i));
		return (ret);
	}
	return (ST_OK);
}

int	token_parse_none(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s (type: %d) (code: %d)", "TT_NONE", lexer->tokens[*i].type, lexer->tokens[*i].code);

	int		ret;

	ret = ST_OK;
	// todo: should be catch in parsing mode F_PARSING_NONE
	if (lexer->tokens[*i].type == TT_ERROR)
		return (ST_PARSER);

	if (lexer->tokens[*i].is_redir_checked == 0
		&& (*i) + 1 < lexer->size && TOKEN_TYPE((*i) + 1) == TT_REDIR)
	{
		return (lexer->tokens[*i + 1].parse(target, parser, lexer, i));
		//return (token_parse_chev_right(target, parser, lexer, i));
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
		ret = s_proc((t_proc *)target, lexer, i);
	}
	(*i)++;
	return (ret);
}
