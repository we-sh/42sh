#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "logger.h"
# include "statuses.h"
# include "shell.h"

# define TOKEN_BUF_SIZE 256

/*
** Typedefs.
*/

typedef enum e_token_type		t_token_type;
typedef enum e_token_code		t_token_code;
typedef struct s_token			t_token;

typedef struct s_lexer_token	t_lexer_token;
typedef struct s_lexer			t_lexer;

typedef struct s_node_job		t_node_job;
typedef struct s_ast			t_ast;

typedef struct s_parser			t_parser;

/*
** Tokens definition.
*/

enum				e_token_type
{
	TT_NONE,
	TT_SEPARATOR,
	TT_INHIBITOR,
	TT_ESCAPE,
	TT_JOBS,
	TT_REDIR,
	TT_SPECIAL,
	TT_NAME,
	TT_ERROR
};

enum				e_token_code
{
	TC_DBL_CHEV_LEFT,
	TC_DBL_CHEV_RIGHT,
	TC_DBL_OR,
	TC_DBL_AND,
	TC_DBL_SEMI,
	TC_SEMI,
	TC_CHEV_RIGHT,
	TC_CHEV_LEFT,
	TC_PIPE,
	TC_AND,
	TC_BACKSLASH,
	TC_DBL_QUOTE,
	TC_QUOTE,
	TC_SPACE,
	TC_TAB,
	TC_NEWLINE,
	TC_NONE
};

/*
** This structure is used into token recognition
*/

struct				s_token
{
	const char		*op;
	size_t			len;
	t_token_type	type;
	t_token_code	code;
	int				(*parse)(t_proc *, t_lexer *, int *);
};

/*
** This structure is used to fill lexer.
*/

struct				s_lexer_token
{
	char			content[256];
	size_t			len;
	t_token_type	type;
	t_token_code	code;
	int				(*parse)(t_proc *, t_lexer *, int *);
};

struct				s_lexer
{
	t_lexer_token	tokens[2048];
	int				size;
	t_sh			*sh;
};

int			parser_process_lexer(t_lexer *lexer, const char *in);
t_token		*token_list(void);
int			tokenize(const char *s, t_lexer *lexer);

int			job_build_unstack_lexer(t_lexer *lexer);
int			job_build_unstack_job_from_lexer(t_job **j, t_lexer *lexer, int *i);
int			job_build_unstack_proc_from_lexer(t_proc *p, t_lexer *lexer, int *i);

/*
** Parser definition.
*/

struct				s_parser
{
	char			*in;
	t_lexer			*lexer;
	t_list			job_head;
};

int	parser_new(t_parser **parser, const char *in);

/*
** Tokenizer/parser definition.
*/

int	token_parse_none(t_proc *proc, t_lexer *lexer, int *i);

// JOBS
int	token_parse_semi(t_proc *proc, t_lexer *lexer, int *i);
int	token_parse_dbl_and(t_proc *proc, t_lexer *lexer, int *i);
int	token_parse_dbl_or(t_proc *proc, t_lexer *lexer, int *i);

// PIPE
int	token_parse_pipe(t_proc *proc, t_lexer *lexer, int *i);

int	token_parse_and(t_proc *proc, t_lexer *lexer, int *i);

// REDIR
int	token_parse_chev_left(t_proc *proc, t_lexer *lexer, int *i);
int	token_parse_chev_right(t_proc *proc, t_lexer *lexer, int *i);
int	token_parse_dbl_chev_left(t_proc *proc, t_lexer *lexer, int *i);
int	token_parse_dbl_chev_right(t_proc *proc, t_lexer *lexer, int *i);

// UTILS
int		token_parse_utils_get_full_word(char **content, t_lexer *lexer, int *i);
int		token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag);
void	token_parse_utils_set_proc_fds(t_proc *p, int fd_l, int fd_r);

// EXPANSIONS
int		expand(t_proc *p, char *content, int is_inhibited);
char	*expand_escape_char(char *buf);
char	*expand_tilde(t_proc *p, char *buf);

// INHIBITORS
int	token_parse_inhib(t_proc *proc, t_lexer *lexer, int *i);

/*
** The array representing each tokens definitions.
** /!\ WARNING: you should put the longest tokens first. /!\
** Otherwise conflits might happen.
** Later we should set TT_SEPARATOR dynamically (IFS)
*/

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

#endif
