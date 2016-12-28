#include "parser.h"

static int	s_none(t_lexer *lexer, int *i)
{
	int		index;
	int		parenthesis_count;
	int		has_tt_name;

	if (TOKEN_CODE(*i) != TC_LPAREN && TOKEN_CODE(*i) != TC_RPAREN)
		return (ST_OK);
	index = *i + (TOKEN_CODE(*i) == TC_LPAREN ? 1 : -1);
	parenthesis_count = 1;
	has_tt_name = 0;
	while ((TOKEN_CODE(*i) == TC_LPAREN ? index < lexer->size : index >= 0)
		&& parenthesis_count > 0)
	{
		if (TOKEN_TYPE(index) == TT_NAME)
			has_tt_name = 1;
		else if (TOKEN_CODE(index) == TC_LPAREN
			|| TOKEN_CODE(index) == TC_RPAREN)
			parenthesis_count += (TOKEN_CODE(index) == TOKEN_CODE(*i) ? 1 : -1);
		index += (TOKEN_CODE(*i) == TC_LPAREN ? 1 : -1);
	}
	if (has_tt_name > 0 && parenthesis_count == 0)
		return (ST_OK);
	if (lexer->notify == 1)
		display_status(ST_PARSER_TOKEN, NULL, lexer->tokens[*i]->content);
	return (ST_PARSER);
}

static int	s_proc(t_proc *p, t_lexer *lexer, int *i)
{
	int		ret;
	int		parenthesis_count;
	char	*cmd;

	if ((cmd = ft_strnew(0)) == NULL)
		return (ST_MALLOC);
	(*i)++;
	parenthesis_count = 1;
	while (*i < lexer->size && parenthesis_count > 0)
	{
		if (TOKEN_CODE(*i) == TC_LPAREN || TOKEN_CODE(*i) == TC_RPAREN)
			parenthesis_count += (TOKEN_CODE(*i) == TC_LPAREN ? 1 : -1);
		if (parenthesis_count == 0)
			break ;
		ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &cmd);
		if (ret != ST_OK)
			return (ret);
		(*i)++;
	}
	if ((ft_array_push_back(&p->argv, cmd)) < 0)
		return (ST_MALLOC);
	p->argc++;
	p->is_subshell = 1;
	free(cmd);
	return (ST_OK);
}

static int	s_jobs(t_job *j, t_lexer *lexer, int *i)
{
	int		ret;
	int		parenthesis_count;

	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
	if (ret != ST_OK)
		return (ret);
	(*i)++;
	parenthesis_count = 1;
	while (*i < lexer->size && parenthesis_count > 0)
	{
		ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
		if (ret != ST_OK)
			return (ret);
		if (TOKEN_CODE(*i) == TC_LPAREN)
			parenthesis_count += 1;
		else if (TOKEN_CODE(*i) == TC_RPAREN)
			parenthesis_count -= 1;
		(*i)++;
	}
	(*i)--;
	if (parenthesis_count > 0)
		return (ST_PARSER); // todo
	return (ST_OK);
}

int			token_parse_subshell(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	(void)parser;
	ret = ST_OK;
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, lexer, i);
	else if (parser->mode == F_PARSING_PROCS)
		ret = s_proc((t_proc *)target, lexer, i);
	(*i)++;
	return (ret);
}
