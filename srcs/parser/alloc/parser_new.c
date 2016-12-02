#include "parser.h"
#include "parser_tokens.h"

/*
** Functions to initialize a new parser
*/

static int	s_build_token_glob_brace(t_parser *parser)
{
	int		i;

	i = 0;
	parser->token_list[i++] = &g_token_glob_brace_pattern_range;
	parser->token_list[i++] = &g_token_glob_brace_pattern_rbrace;
	parser->token_list[i++] = &g_token_glob_brace_pattern_lbrace;
	parser->token_list[i++] = &g_token_glob_brace_pattern_sep;
	parser->token_list[i++] = NULL;
	return (ST_OK);
}

static int	s_build_token_globing(t_parser *parser)
{
	int		i;

	i = 0;
	parser->token_list[i++] = &g_token_globing_inhibitor_dquote;
	parser->token_list[i++] = &g_token_globing_inhibitor_quote;
	parser->token_list[i++] = &g_token_globing_name_tilde;
	parser->token_list[i++] = NULL;
	return (ST_OK);
}

static int	s_build_token_command_part2(t_parser *parser, int i)
{
	parser->token_list[i++] = &g_token_separator_space;
	parser->token_list[i++] = &g_token_separator_tab;
	parser->token_list[i++] = &g_token_separator_newline;
	parser->token_list[i++] = &g_token_name_rbrace;
	parser->token_list[i++] = &g_token_name_lbrace;
	parser->token_list[i++] = &g_token_name_bquote;
	parser->token_list[i++] = NULL;
	return (ST_OK);
}

static int	s_build_token_command(t_parser *parser)
{
	int		i;

	i = 0;
	parser->token_list[i++] = &g_token_redir_dless;
	parser->token_list[i++] = &g_token_redir_dgreat;
	parser->token_list[i++] = &g_token_jobs_or_if;
	parser->token_list[i++] = &g_token_jobs_and_if;
	parser->token_list[i++] = &g_token_error_dsemi;
	parser->token_list[i++] = &g_token_redir_clobber;
	parser->token_list[i++] = &g_token_redir_andgreat;
	parser->token_list[i++] = &g_token_redir_greatand;
	parser->token_list[i++] = &g_token_redir_lessand;
	parser->token_list[i++] = &g_token_jobs_semi;
	parser->token_list[i++] = &g_token_redir_great;
	parser->token_list[i++] = &g_token_redir_less;
	parser->token_list[i++] = &g_token_redir_pipe;
	parser->token_list[i++] = &g_token_special_and;
	parser->token_list[i++] = &g_token_subshell_lparen;
	parser->token_list[i++] = &g_token_subshell_rparen;
	parser->token_list[i++] = &g_token_inhibitor_dquote;
	parser->token_list[i++] = &g_token_inhibitor_quote;
	parser->token_list[i++] = &g_token_name_backslash;
	return (s_build_token_command_part2(parser, i));
}

static int	s_parser_new_part2(t_parser **parser, int mode)
{
	if (mode == F_PARSING_TERMCAPS)
		(*parser)->unstack_func = NULL;
	else if (mode == F_PARSING_JOBS)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_job;
	else if (mode == F_PARSING_PROCS)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_proc;
	else if (mode == F_PARSING_NONE)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_none;
	else if (mode == F_PARSING_GLOBING)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_globing;
	else if (mode == F_PARSING_GLOB_BRACE)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_glob_brace;
	else
		return (ST_EINVAL);
	return (ST_OK);
}

int			parser_new(t_parser **parser, const char *in, t_sh *sh, int mode)
{
	if (!(*parser = ft_memalloc(sizeof(t_parser))))
		return (ST_MALLOC);
	if (!((*parser)->in = ft_strdup(in)))
		return (ST_MALLOC);
	if (!((*parser)->lexer = ft_memalloc(sizeof(t_lexer))))
		return (ST_MALLOC);
	(*parser)->lexer->sh = sh;
	(*parser)->lexer->size = 0;
	(*parser)->lexer->notify = 1;
	(*parser)->lexer->parenthesis_count = 0;
	(*parser)->mode = mode;
	(*parser)->target_list_head = NULL;
	(*parser)->sh = sh;
	if (((*parser)->lexer->buf = ft_strnew(TOKEN_BUFFER_REALLOC)) == NULL)
		return (ST_MALLOC);
	(*parser)->lexer->buf_allocated_size = TOKEN_BUFFER_REALLOC;
	(*parser)->lexer->is_inhibited = 0;
	(*parser)->lexer->is_parenthesized = 0;
	if (lexer_tokens_alloc((*parser)->lexer) != ST_OK)
		return (ST_MALLOC);
	if (mode == F_PARSING_GLOBING)
		s_build_token_globing(*parser);
	else if (mode == F_PARSING_GLOB_BRACE)
		s_build_token_glob_brace(*parser);
	else
		s_build_token_command(*parser);
	return (s_parser_new_part2(parser, mode));
}
