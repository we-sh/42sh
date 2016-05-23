# include "shell.h"

/*
** This file refers all tokens operators.
** Warning: you should put the longest tokens first.
** Otherwise conflits might happen.
** Token types are defined into incs/lexer.h
*/

static const t_token tokens[] = {
	{">>", 2, TOKEN_REDIR},
	{"<<", 2, TOKEN_REDIR},
	{"||", 2, TOKEN_DBL_OR},
	{">|", 2, TOKEN_REDIR},
	{"<>", 2, TOKEN_REDIR},
	{"<&", 2, TOKEN_REDIR},
	{">&", 2, TOKEN_REDIR},
	{"&&", 2, TOKEN_DBL_AND},
	{";;", 2, TOKEN_DBL_SEMI},
	{"|", 1, TOKEN_PIPE},
	{"&", 1, TOKEN_AND},
	{">", 1, TOKEN_REDIR},
	{"<", 1, TOKEN_REDIR},
	{";", 1, TOKEN_SEMI},
	{"\\", 1, TOKEN_BACKSLASH},
	{"\"", 1, TOKEN_INHIB},
	{"'", 1, TOKEN_INHIB},
	{" ", 1, TOKEN_ESP},
	{"\n", 1, TOKEN_ESP},
	{"\v", 1, TOKEN_ESP},
	{"\t", 1, TOKEN_ESP},
	{"\r", 1, TOKEN_ESP},
	{"\f", 1, TOKEN_ESP},
	{NULL, 1, 0}
};

t_token *token_list(void)
{
	return (t_token *)tokens;
}
