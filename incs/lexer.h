#ifndef TOKEN_H
# define TOKEN_H

#define TOKEN_BUF_SIZE 256

typedef enum 	e_token_type
{
	NOT_A_TOKEN,
	TOKEN_ESP,
	TOKEN_SEMI,
	TOKEN_BACKSLASH,
	TOKEN_INHIB,
	TOKEN_DBL_SEMI,
	TOKEN_DBL_AND,
	TOKEN_DBL_OR,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_REDIR,
	TOKEN_NAME
}				t_token_type;

typedef struct s_token
{
	const char		*op;
	int				size;
	t_token_type	type;
} 				t_token;

typedef struct 	s_lexer_token
{
	char			content[128]; /* Replace with dynamic array */
	int				size;
	t_token_type	type;
} 				t_lexer_token;

typedef struct	s_lexer
{
  t_lexer_token tokens[2048];  /* Replace with dynamic array */
  int			size;
}				t_lexer;

#endif
