#ifndef PARSER_TOKENS_H
# define PARSER_TOKENS_H

static t_token g_token_redir_dless = {
	"<<",
	NULL,
	2,
	TT_REDIR,
	TC_DLESS,
	token_parse_dless,
	0
};

static t_token g_token_redir_dgreat = {
	">>",
	NULL,
	2,
	TT_REDIR,
	TC_DGREAT,
	token_parse_dgreat,
	0
};

static t_token g_token_jobs_or_if = {
	"||",
	NULL,
	2,
	TT_JOBS,
	TC_OR_IF,
	token_parse_or_if,
	0
};

static t_token g_token_jobs_and_if = {
	"&&",
	NULL,
	2,
	TT_JOBS,
	TC_AND_IF,
	token_parse_and_if,
	0
};

static t_token g_token_error_dsemi = {
	";;",
	NULL,
	2,
	TT_ERROR,
	TC_DSEMI,
	token_parse_none,
	0
};

static t_token g_token_redir_clobber = {
	">|",
	NULL,
	2,
	TT_REDIR,
	TC_CLOBBER,
	token_parse_great,
	0
};

static t_token g_token_redir_andgreat = {
	"&>",
	NULL,
	2,
	TT_REDIR,
	TC_ANDGREAT,
	token_parse_andgreat,
	0
};

static t_token g_token_redir_greatand = {
	">&",
	NULL,
	2,
	TT_REDIR,
	TC_GREATAND,
	token_parse_greatand,
	0
};

static t_token g_token_redir_lessand = {
	"<&",
	NULL,
	2,
	TT_REDIR,
	TC_LESSAND,
	token_parse_lessand,
	0
};

static t_token g_token_jobs_semi = {
	";",
	NULL,
	1,
	TT_JOBS,
	TC_SEMI,
	token_parse_semi,
	0
};

static t_token g_token_redir_great = {
	">",
	NULL,
	1,
	TT_REDIR,
	TC_GREAT,
	token_parse_great,
	0
};

static t_token g_token_redir_less = {
	"<",
	NULL,
	1,
	TT_REDIR,
	TC_LESS,
	token_parse_less,
	0
};

static t_token g_token_redir_pipe = {
	"|",
	NULL,
	1,
	TT_REDIR,
	TC_PIPE,
	token_parse_pipe,
	0
};

static t_token g_token_special_and = {
	"&",
	NULL,
	1,
	TT_SPECIAL,
	TC_AND,
	token_parse_and,
	0
};

static t_token g_token_inhibitor_dquote = {
	"\"",
	NULL,
	1,
	TT_INHIBITOR,
	TC_DQUOTE,
	token_parse_inhib,
	0
};

static t_token g_token_inhibitor_quote = {
	"'",
	NULL,
	1,
	TT_INHIBITOR,
	TC_QUOTE,
	token_parse_inhib,
	0
};

static t_token g_token_separator_space = {
	" ",
	NULL,
	1,
	TT_SEPARATOR,
	TC_SPACE,
	token_parse_separator,
	0
};

static t_token g_token_separator_tab = {
	"\t",
	NULL,
	1,
	TT_SEPARATOR,
	TC_TAB,
	token_parse_separator,
	0
};

static t_token g_token_separator_newline = {
	"\n",
	NULL,
	1,
	TT_SEPARATOR,
	TC_NEWLINE,
	token_parse_separator,
	0
};

static t_token g_token_name_backslash = {
	"\\",
	NULL,
	1,
	TT_NAME,
	TC_BACKSLASH,
	token_parse_none,
	0
};

static t_token g_token_subshell_lparen = {
	"(",
	NULL,
	1,
	TT_SUBSHELL,
	TC_LPAREN,
	token_parse_subshell,
	0
};

static t_token g_token_subshell_rparen = {
	")",
	NULL,
	1,
	TT_SUBSHELL,
	TC_RPAREN,
	token_parse_subshell,
	0
};

static t_token g_token_name_bquote = {
	"`",
	NULL,
	1,
	TT_INHIBITOR,
	TC_BQUOTE,
	token_parse_none,
	0
};

static t_token g_token_name_lbrace = {
	"{",
	NULL,
	1,
	TT_NAME,
	TC_LBRACE,
	token_parse_none,
	0
};

static t_token g_token_name_rbrace = {
	"}",
	NULL,
	1,
	TT_NAME,
	TC_RBRACE,
	token_parse_none,
	0
};

/*
** Tokens for parameters expansion (globing)
*/

static t_token g_token_var_inhibitor_dquote = {
	"\"",
	NULL,
	1,
	TT_INHIBITOR,
	TC_DQUOTE,
	token_var_parse_inhib,
	0
};

static t_token g_token_var_inhibitor_quote = {
	"'",
	NULL,
	1,
	TT_INHIBITOR,
	TC_QUOTE,
	token_var_parse_inhib,
	0
};


/*
** Tokens for glob brace expansion `{}`
*/

static t_token g_token_glob_brace_pattern_range = {
	"..",
	NULL,
	2,
	TT_PATTERN,
	TC_RANGE,
	token_glob_brace_parse_pattern,
	0
};

static t_token g_token_glob_brace_pattern_lbrace = {
	"{",
	NULL,
	1,
	TT_PATTERN,
	TC_LBRACE,
	token_glob_brace_parse_pattern,
	0
};

static t_token g_token_glob_brace_pattern_rbrace = {
	"}",
	NULL,
	1,
	TT_PATTERN,
	TC_RBRACE,
	token_glob_brace_parse_pattern,
	0
};

static t_token g_token_glob_brace_pattern_sep = {
	",",
	NULL,
	1,
	TT_PATTERN,
	TC_COMMA,
	token_glob_brace_parse_pattern,
	0
};

#endif
