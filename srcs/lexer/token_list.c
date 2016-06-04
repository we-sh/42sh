#include "shell.h"

/*
** This file refers all tokens operators.
** /!\ WARNING: you should put the longest tokens first. /!\
** Otherwise conflits might happen.
** Token types and codes are defined into incs/lexer.h
** Later we should set TT_SEPARATOR dynamically (IFS)
*/

static const t_token g_tokens[] = {
	{"<<", 2, TT_REDIR, TC_DBL_CHEV_LEFT},
	{">>", 2, TT_REDIR, TC_DBL_CHEV_RIGHT},
	{"||", 2, TT_JOBS, TC_DBL_OR},
	{"&&", 2, TT_JOBS, TC_DBL_AND},
	{";;", 2, TT_ERROR, TC_DBL_SEMI},
	{";", 1, TT_JOBS, TC_SEMI},
	{">", 1, TT_REDIR, TC_CHEV_RIGHT},
	{"<", 1, TT_REDIR, TC_CHEV_LEFT},
	{"|", 1, TT_REDIR, TC_PIPE},
	{"&", 1, TT_SPECIAL, TC_AND},
	{"\\", 1, TT_ESCAPE, TC_BACKSLASH},
	{"\"", 1, TT_INHIBITOR, TC_DBL_QUOTE},
	{"'", 1, TT_INHIBITOR, TC_QUOTE},
	{" ", 1, TT_SEPARATOR, TC_SPACE},
	{"\t", 1, TT_SEPARATOR, TC_TAB},
	{"\n", 1, TT_SEPARATOR, TC_NEWLINE},
	{NULL, 1, TT_NONE, TC_NONE}
};

t_token	*token_list(void)
{
	return (t_token *)g_tokens;
}
