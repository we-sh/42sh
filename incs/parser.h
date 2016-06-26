#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "logger.h"
# include "statuses.h"
# include "shell.h"

# define TOKEN_BUFFER_REALLOC 4096
# define TOKEN_LIST_REALLOC 20

# define TOKEN_CODE(i)		({lexer->tokens[i]->code;})
# define TOKEN_CONTENT(i)	({lexer->tokens[i]->content;})
# define TOKEN_TYPE(i)		({lexer->tokens[i]->type;})

# define P_TOKEN_CODE(i)	({parser->lexer->tokens[i]->code;})
# define P_TOKEN_CONTENT(i)	({parser->lexer->tokens[i]->content;})
# define P_TOKEN_TYPE(i)	({parser->lexer->tokens[i]->type;})

/*
** Typedefs.
*/

typedef struct s_token			t_token;
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
	TC_DLESS,
	TC_DGREAT,
	TC_OR_IF,
	TC_AND_IF,
	TC_DSEMI,
	TC_CLOBBER,
	TC_SEMI,
	TC_GREAT,
	TC_LESS,
	TC_PIPE,
	TC_AND,
	TC_ANDGREAT,
	TC_GREATAND,
	TC_LESSAND,
	TC_LBRACE,
	TC_RBRACE,
	TC_BQUOTE,
	TC_BACKSLASH,
	TC_DQUOTE,
	TC_QUOTE,
	TC_SPACE,
	TC_TAB,
	TC_NEWLINE,
	TC_TILDE,
	TC_NONE,
	TC_TOTAL
}					t_token_code;

/*
** This structure is used to fill lexer.
*/

struct				s_token
{
	const char		*op;
	char			*content;
	int				len;
	t_token_type	type;
	t_token_code	code;
	int				(*parse)(void *, t_parser *, t_lexer *, int *);
	int				is_redir_checked;
};

struct				s_lexer
{
	t_token			**tokens;
	int				size;
	int				allocated_size;
	char			*buf;
	int				buf_allocated_size;
	int				buf_index;
	int				is_inhibited;
	int				is_parenthesized;
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
	F_PARSING_PROCS,
	F_PARSING_GLOBING
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
	t_token			*token_list[TC_TOTAL];
	t_parsing_mode	mode;
	t_sh			*sh;
};

/*
** Expansion definitions
*/

typedef struct				s_argv
{
	t_list					argv_list;
	char					*buffer;
}							t_argv;


/*
** Lexer functions.
*/

int		lexer(t_parser *parser, const char *in);
int		lexer_tokenize(const char *s, t_parser *parser, t_lexer *lexer);
int		lexer_tokens_alloc(t_lexer *lexer);
int		lexer_tokens_realloc(t_lexer *lexer);
int		lexer_bufferize(t_lexer *lexer, const char *str, int len);
t_token	*lexer_token_recognizer(t_parser *parser, const char *s, int i);
int		lexer_buffer_dump(t_parser *parser, t_lexer *lexer);
int		lexer_token_add(t_lexer *lexer, const char *str, t_token token);

/*
** Parser functions.
*/


int		parser_new(t_parser **parser, const char *in, t_sh *sh, int mode);

int		parser_build_list_unstack_lexer(t_parser *parser);
int		parser_build_list_unstack_lexer_none(t_parser *parser, t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_job(t_parser *parser, t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_proc(t_parser *parser, t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_globing(t_parser *parser, t_lexer *lexer, int *i);

/*
** Expansion.
*/

int		expand(t_lexer *lexer, t_proc *p, int *i);
char	*expand_escape_char(char *buf);

/*
** Function pointers for the parser.
*/

// Default function.
int		token_parse_none(void *target, t_parser *parser, t_lexer *lexer, int *i);

// Jobs.
int		token_parse_semi(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_and_if(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_or_if(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

// Pipe,
int		token_parse_pipe(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

// And.
int		token_parse_and(void *target, t_parser *parser, t_lexer *lexer, int *i);

// Redirections.
int		token_parse_less(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_great(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_dless(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_dgreat(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_andgreat(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_greatand(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_lessand(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

// Function pointers utils.
int		token_parse_utils_skip_separators(t_lexer *lexer, int *i,
			char **command);
int		token_parse_utils_get_full_word(char **content, t_lexer *lexer, int *i);
int		token_parse_utils_get_word_and_inhib(char **content, t_lexer *lexer,
			int *i)
int		token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag);
void	token_parse_utils_set_proc_fds(t_proc *p, int fd_l, int fd_r);
int		token_parse_utils_push_command(char *content, char **target);
int		token_parse_utils_check_char_to_fd(char *f, int *fd);
int		token_parse_utils_gen_token_after_dash(t_proc *p, t_parser *parser,
			t_lexer *lexer, int *i);
int		token_globing_parse_utils_push_str(t_list *head, char *str);

// Inhibitors.
int		token_parse_inhib(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

// Substitution
int		token_parse_bquote(void *target, t_parser *parser, t_lexer *lexer,
			int *i);


// Separators.
int		token_parse_separator(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

// Globing.
int		token_parse_lbrace(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_rbrace(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

// Globing
int		token_globing_parse_none(void *target, t_parser *parser,
			t_lexer *lexer, int *i);
int		token_globing_parse_inhib(void *target, t_parser *parser,
			t_lexer *lexer, int *i);

#endif
