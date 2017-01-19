#ifndef PARSER_STRUCT_H
# define PARSER_STRUCT_H

/*
** Typedefs.
*/

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

typedef struct s_parser	t_parser;

typedef struct			s_quoting
{
	int					quote;
	int					dbquote;
	int					bkquote;
	int					bkslash;
	int					pipe;
}						t_quoting;

/*
** Tokens definition.
*/

typedef enum			e_token_type
{
	TT_NONE,
	TT_SEPARATOR,
	TT_INHIBITOR,
	TT_JOBS,
	TT_REDIR,
	TT_SPECIAL,
	TT_NAME,
	TT_SUBSHELL,
	TT_PATTERN,
	TT_ERROR
}						t_token_type;

typedef enum			e_token_code
{
	TC_NONE,
	TC_DLESS,
	TC_DGREAT,
	TC_OR_IF,
	TC_AND_IF,
	TC_DSEMI,
	TC_DOLLAR,
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
	TC_LPAREN,
	TC_RPAREN,
	TC_RANGE,
	TC_COMMA,
	TC_TOTAL
}						t_token_code;

/*
* Patterns defintion for GLOB_BRACE
*/

typedef enum			e_glob_brace_pattern_type
{
	T_PATTERN_NONE,
	T_PATTERN_LIST,
	T_PATTERN_NUMERIC_RANGE,
	T_PATTERN_ASCII_RANGE
}						t_glob_brace_pattern_type;

/*
** This structure is used to fill lexer.
*/

struct					s_token
{
	const char		*op;
	char			*content;
	int				len;
	t_token_type	type;
	t_token_code	code;
	int				(*parse)(void *, t_parser *, t_lexer *, int *);
	int				is_redir_checked;
};

struct					s_lexer
{
	t_token			**tokens;
	int				size;
	int				allocated_size;
	char			*buf;
	int				buf_allocated_size;
	int				buf_index;
	int				is_inhibited;
	int				is_parenthesized;
	int				parenthesis_count;
	int				notify;
	t_sh			*sh;
};

/*
** Parsing mode definition
*/

typedef enum			e_parsing_mode
{
	F_PARSING_NONE,
	F_PARSING_TERMCAPS,
	F_PARSING_JOBS,
	F_PARSING_PROCS,
	F_PARSING_VAR,
	F_PARSING_GLOB_BRACE
}						t_parsing_mode;

/*
** Parser definition.
*/

struct					s_parser
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

typedef struct			s_argv
{
	t_list					argv_list;
	char					*buffer;
	int						pos;
	int						is_null;
}						t_argv;

#endif
