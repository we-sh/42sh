#ifndef LEXER_H
# define LEXER_H

# define TOKEN_BUF_SIZE 256

/*
** Refers to category
*/

typedef enum	e_token_type
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
}				t_token_type;

/*
** Refers to token symbol
** Should be unique for each operators
*/

typedef enum	e_token_code
{
	TC_NONE,
	TC_BACKSLASH,
	TC_QUOTE,
	TC_DBL_QUOTE,
	TC_DBL_SEMI,
	TC_DBL_AND,
	TC_DBL_OR,
	TC_DBL_CHEV_LEFT,
	TC_DBL_CHEV_RIGHT,
	TC_CHEV_RIGHT,
	TC_CHEV_LEFT,
	TC_SEMI,
	TC_PIPE,
	TC_SPACE,
	TC_TAB,
	TC_NEWLINE,
	TC_AND
}				t_token_code;

typedef struct	s_token
{
	const char		*op;
	size_t			len;
	t_token_type	type;
	t_token_code	code;
}				t_token;

typedef struct	s_lexer_token
{
	char			content[256]; /* Replace with dynamic array */
	size_t			len;
	t_token_type	type;
	t_token_code	code;
}				t_lexer_token;

typedef struct	s_lexer
{
	t_lexer_token	tokens[2048];  /* Replace with dynamic array */
	int				size;
}				t_lexer;

#endif
