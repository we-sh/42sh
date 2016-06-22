#include "parser.h"

/*
** Create a new parser structure and initialize its fields.
** The input string is duplicated and the other are allocated.
*/


static t_token g_token_redir_dbl_chev_left = {
	"<<",
	2,
	TT_REDIR,
	TC_DBL_CHEV_LEFT,
	token_parse_dbl_chev_left
};

static t_token g_token_redir_dbl_chev_right = {
	">>",
	2,
	TT_REDIR,
	TC_DBL_CHEV_RIGHT,
	token_parse_dbl_chev_right
};

static t_token g_token_jobs_dbl_or = {
	"||",
	2,
	TT_JOBS,
	TC_DBL_OR,
	token_parse_dbl_or
};

static t_token g_token_jobs_dbl_and = {
	"&&",
	2,
	TT_JOBS,
	TC_DBL_AND,
	token_parse_dbl_and
};

static t_token g_token_error_dbl_semi = {
	";;",
	2,
	TT_ERROR,
	TC_DBL_SEMI,
	token_parse_none
};

static t_token g_token_redir_chev_right_2 = {
	">|",
	2,
	TT_REDIR,
	TC_CHEV_RIGHT,
	token_parse_chev_right
};

static t_token g_token_jobs_semi = {
	";",
	1,
	TT_JOBS,
	TC_SEMI,
	token_parse_semi
};

static t_token g_token_redir_chev_right = {
	">",
	1,
	TT_REDIR,
	TC_CHEV_RIGHT,
	token_parse_chev_right
};

static t_token g_token_redir_chev_left = {
	"<",
	1,
	TT_REDIR,
	TC_CHEV_LEFT,
	token_parse_chev_left
};

static t_token g_token_redir_pipe = {
	"|",
	1,
	TT_REDIR,
	TC_PIPE,
	token_parse_pipe
};

static t_token g_token_special_and = {
	"&",
	1,
	TT_SPECIAL,
	TC_AND,
	token_parse_and
};

static t_token g_token_inhibitor_dbl_quote = {
	"\"",
	1,
	TT_INHIBITOR,
	TC_DBL_QUOTE,
	token_parse_inhib
};

static t_token g_token_inhibitor_quote = {
	"'",
	1,
	TT_INHIBITOR,
	TC_QUOTE,
	token_parse_inhib
};

static t_token g_token_separator_space = {
	" ",
	1,
	TT_SEPARATOR,
	TC_SPACE,
	token_parse_none
};

static t_token g_token_separator_tab = {
	"\t",
	1,
	TT_SEPARATOR,
	TC_TAB,
	token_parse_none
};

static t_token g_token_separator_newline = {
	"\n",
	1,
	TT_SEPARATOR,
	TC_NEWLINE,
	token_parse_none
};

static t_token g_token_none_backslash = {
	"\\",
	1,
	TT_NONE,
	TC_BACKSLASH,
	token_parse_none
};

static int	s_build_token_list(t_parser *parser)
{
	int		i;

	i = 0;
	parser->token_list[i++] = &g_token_redir_dbl_chev_left;
	parser->token_list[i++] = &g_token_redir_dbl_chev_right;
	parser->token_list[i++] = &g_token_jobs_dbl_or;
	parser->token_list[i++] = &g_token_jobs_dbl_and;
	parser->token_list[i++] = &g_token_error_dbl_semi;
	parser->token_list[i++] = &g_token_redir_chev_right_2;
	parser->token_list[i++] = &g_token_jobs_semi;
	parser->token_list[i++] = &g_token_redir_chev_right;
	parser->token_list[i++] = &g_token_redir_chev_left;
	parser->token_list[i++] = &g_token_redir_pipe;
	parser->token_list[i++] = &g_token_special_and;
	parser->token_list[i++] = &g_token_inhibitor_dbl_quote;
	parser->token_list[i++] = &g_token_inhibitor_quote;
	parser->token_list[i++] = &g_token_none_backslash;
	parser->token_list[i++] = &g_token_separator_space;
	parser->token_list[i++] = &g_token_separator_tab;
	parser->token_list[i++] = &g_token_separator_newline;
	parser->token_list[i++] = NULL;
	return (ST_OK);
}

int	parser_new(t_parser **parser, const char *in, t_sh *sh, int mode)
{
	if (!in)
		return (ST_EINVAL);
	if (!(*parser = ft_memalloc(sizeof(t_parser))))
		return (ST_MALLOC);
	if (!((*parser)->in = ft_strdup(in)))
		return (ST_MALLOC);
	if (!((*parser)->lexer = ft_memalloc(sizeof(t_lexer))))
		return (ST_MALLOC);
	(*parser)->lexer->sh = sh;
	// TODO : make dynamic token list
	(*parser)->mode = mode;
	(*parser)->target_list_head = NULL;
	(*parser)->sh = sh;
	s_build_token_list(*parser);

	// assign the unstack function according to the parsing mode
	if (mode == F_PARSING_TERMCAPS)
		(*parser)->unstack_func = NULL;
	else if (mode == F_PARSING_JOBS)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_job;
	else if (mode == F_PARSING_PROCS)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_proc;
	else if (mode == F_PARSING_NONE)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_none;
	else
	{
		log_error("parsing mode not yet supported (%d)", mode);
		return (ST_EINVAL);
	}

	return (ST_OK);
}
