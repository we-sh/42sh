#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "logger.h"
# include "statuses.h"
# include "shell.h"

# define TOKEN_BUF_SIZE 256

# define TOKEN_CODE(i)		({lexer->tokens[i].code;})
# define TOKEN_CONTENT(i)	({lexer->tokens[i].content;})
# define TOKEN_TYPE(i)		({lexer->tokens[i].type;})

# define P_TOKEN_CODE(i)	({parser->lexer->tokens[i].code;})
# define P_TOKEN_CONTENT(i)	({parser->lexer->tokens[i].content;})
# define P_TOKEN_TYPE(i)	({parser->lexer->tokens[i].type;})

/*
** Typedefs.
*/

typedef struct s_token			t_token;
/* TODO " sure we can delete one of t_token or t_lexer_token... */
typedef struct s_lexer_token	t_lexer_token;
typedef struct s_lexer			t_lexer;

typedef struct s_parser			t_parser;

/*
** Tokens definition.
*/

typedef enum		e_token_type
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
}					t_token_type;

typedef enum		e_token_code
{
	TC_DBL_CHEV_LEFT,
	TC_DGREAT,
	TC_OR_IF,
	TC_DBL_AND,
	TC_DBL_SEMI,
	TC_SEMI,
	TC_CHEV_RIGHT,
	TC_CHEV_LEFT,
	TC_PIPE,
	TC_AND,
	TC_ANDGREAT,
	TC_BACKSLASH,
	TC_DBL_QUOTE,
	TC_QUOTE,
	TC_SPACE,
	TC_TAB,
	TC_NEWLINE,
	TC_NONE
}					t_token_code;

/*
** This structure is used into token recognition
*/

struct				s_token
{
	const char		*op;
	size_t			len;
	t_token_type	type;
	t_token_code	code;
	int				(*parse)(void *, t_parser *, t_lexer *, int *);
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
	int				(*parse)(void *, t_parser *, t_lexer *, int *);
};

struct				s_lexer
{
	t_lexer_token	tokens[2048];
	int				size;
	t_sh			*sh;
};

/*
** Parsing mode definition
*/

typedef enum		s_parsing_mode
{
	F_PARSING_NONE,
	F_PARSING_TERMCAPS,
	F_PARSING_JOBS,
	F_PARSING_PROCS
}					t_parsing_mode;

/*
** Parser definition.
*/

struct				s_parser
{
	char			*in;
	t_lexer			*lexer;
	t_list			*target_list_head;
	int				(*unstack_func)(t_parser *, t_lexer *, int *);
	t_token			*token_list[20];
	t_parsing_mode	mode;
	t_sh			*sh;
};

/*
** Lexer functions.
*/

t_token	*token_list(void);
int		tokenize(const char *s, t_parser *parser);

/*
** Parser functions.
*/

int		parser_process_lexer(t_parser *parser, const char *in);

int		parser_new(t_parser **parser, const char *in, t_sh *sh, int mode);

int		parser_build_list_unstack_lexer(t_parser *parser);
int		parser_build_list_unstack_lexer_none(t_parser *parser, t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_job(t_parser *parser, t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_proc(t_parser *parser, t_lexer *lexer, int *i);

/*
** Expansion.
*/

int		expand(t_sh *sh, t_proc *p, char *content, int is_inhibited);
char	*expand_escape_char(char *buf);
char	*expand_tilde(t_sh *sh, char *buf);

/*
** Function pointers for the parser.
*/

// Default function.
int		token_parse_none(void *target, t_parser *parser, t_lexer *lexer, int *i);

// Jobs.
int		token_parse_semi(void *target, t_parser *parser, t_lexer *lexer, int *i);
int		token_parse_dbl_and(void *target, t_parser *parser, t_lexer *lexer, int *i);
int		token_parse_or_if(void *target, t_parser *parser, t_lexer *lexer, int *i);

// Pipe,
int		token_parse_pipe(void *target, t_parser *parser, t_lexer *lexer, int *i);

// And.
int		token_parse_and(void *target, t_parser *parser, t_lexer *lexer, int *i);

// Redirections.
int		token_parse_chev_left(void *target, t_parser *parser, t_lexer *lexer, int *i);
int		token_parse_chev_right(void *target, t_parser *parser, t_lexer *lexer, int *i);
int		token_parse_dbl_chev_left(void *target, t_parser *parser, t_lexer *lexer, int *i);
int		token_parse_dgreat(void *target, t_parser *parser, t_lexer *lexer, int *i);
int		token_parse_andgreat(void *target, t_parser *parser, t_lexer *lexer, int *i);

// Function pointers utils.
int		token_parse_utils_get_full_word(char **content, t_lexer *lexer, int *i);
int		token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag);
void	token_parse_utils_set_proc_fds(t_proc *p, int fd_l, int fd_r);
int		token_parse_utils_push_command(char *content, char **target);

// Inhibitors.
int		token_parse_inhib(void *target, t_parser *parser, t_lexer *lexer, int *i);

#endif
