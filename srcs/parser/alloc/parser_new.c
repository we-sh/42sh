#include "parser.h"

/*
** Create a new parser structure and initialize its fields.
** The input string is duplicated and the other are allocated.
*/

/*
static const t_token g_tokens[] = {
	{"<<",	2,	TT_REDIR,		TC_DBL_CHEV_LEFT,	token_parse_dbl_chev_left},
	{">>",	2,	TT_REDIR,		TC_DBL_CHEV_RIGHT,	token_parse_dbl_chev_right},
	{"||",	2,	TT_JOBS,		TC_DBL_OR,			token_parse_dbl_or},
	{"&&",	2,	TT_JOBS,		TC_DBL_AND,			token_parse_dbl_and},
	{";;",	2,	TT_ERROR,		TC_DBL_SEMI,		token_parse_none},
	{">|",	2,	TT_REDIR,		TC_CHEV_RIGHT,		token_parse_chev_right},
	{";",	1,	TT_JOBS,		TC_SEMI,			token_parse_semi},
	{">",	1,	TT_REDIR,		TC_CHEV_RIGHT,		token_parse_chev_right},
	{"<",	1,	TT_REDIR,		TC_CHEV_LEFT,		token_parse_chev_left},
	{"|",	1,	TT_REDIR,		TC_PIPE,			token_parse_pipe},
	{"&",	1,	TT_SPECIAL,		TC_AND,				token_parse_and},
	//{"\\",	1,	TT_INHIBITOR,	TC_BACKSLASH,		token_parse_inhib},
	{"\"",	1,	TT_INHIBITOR,	TC_DBL_QUOTE,		token_parse_inhib},
	{"'",	1,	TT_INHIBITOR,	TC_QUOTE,			token_parse_inhib},
	{" ",	1,	TT_SEPARATOR,	TC_SPACE,			token_parse_none},
	{"\t",	1,	TT_SEPARATOR,	TC_TAB,				token_parse_none},
	{"\n",	1,	TT_SEPARATOR,	TC_NEWLINE,			token_parse_none},
	{NULL,	1,	TT_NONE,		TC_NONE,			token_parse_none}
};
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

static t_token g_token_separator_newline = {
	"\n",
	1,
	TT_SEPARATOR,
	TC_NEWLINE,
	token_parse_none
};

static t_token g_token_none_none = {
	NULL,
	1,
	TT_NONE,
	TC_NONE,
	token_parse_none
};

static int	s_build_token_list(t_parser *parser)
{
	parser->token_list[0] = &g_token_redir_dbl_chev_left;
	parser->token_list[1] = &g_token_redir_dbl_chev_right;
	parser->token_list[2] = &g_token_none_none;
	parser->token_list[3] = &g_token_separator_newline;
	parser->token_list[4] = NULL;
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
	// TODO : create and assign specific functions for jobs/proc according to parsing mode
	(*parser)->unstack_func = &job_build_unstack_job_from_lexer;
	s_build_token_list(*parser);
	return (ST_OK);
}
