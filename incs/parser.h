#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "logger.h"
# include "statuses.h"
# include "shell.h"
# include "parser_struct.h"

# define TOKEN_BUFFER_REALLOC 1024
# define TOKEN_LIST_REALLOC 20

# define TOKEN_CODE(i)		({lexer->tokens[i]->code;})
# define TOKEN_CONTENT(i)	({lexer->tokens[i]->content;})
# define TOKEN_TYPE(i)		({lexer->tokens[i]->type;})

# define P_TOKEN_CODE(i)	({parser->lexer->tokens[i]->code;})
# define P_TOKEN_CONTENT(i)	({parser->lexer->tokens[i]->content;})
# define P_TOKEN_TYPE(i)	({parser->lexer->tokens[i]->type;})

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
int		parser_build_list_unstack_lexer_none(t_parser *parser,
										t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_job(t_parser *parser,
										t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_proc(t_parser *parser,
										t_lexer *lexer, int *i);
int		parser_build_list_unstack_lexer_globing(t_parser *parser,
										t_lexer *lexer, int *i);

/*
** Expansion.
*/

int		expand(t_lexer *lexer, t_proc *p, int *i);

/*
** Globbing.
*/

int		globbing(t_list **argv_list);
int		globbing_interrogation(t_list **argv_list);

/*
** Function pointers for the parser.
*/

int		token_parse_none(void *target, t_parser *parser,
						t_lexer *lexer, int *i);

int		token_parse_semi(void *target, t_parser *parser,
						t_lexer *lexer, int *i);
int		token_parse_and_if(void *target, t_parser *parser,
						t_lexer *lexer, int *i);
int		token_parse_or_if(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_parse_pipe(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_parse_and(void *target, t_parser *parser, t_lexer *lexer, int *i);

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
int		token_parse_subshell(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_parse_utils_skip_separators(t_lexer *lexer, int *i,
			char **command);
int		token_parse_utils_get_full_word(char **content, t_lexer *lexer, int *i);
int		token_parse_utils_get_word_and_inhib(char **content, t_lexer *lexer,
			int *i);
int		token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag);
void	token_parse_utils_set_proc_fds(t_proc *p, int fd_l, int fd_r);
int		token_parse_utils_push_command(char *content, char **target);
int		token_parse_utils_check_char_to_fd(char *f, int *fd);
int		token_parse_utils_gen_token_after_dash(t_proc *p, t_parser *parser,
			t_lexer *lexer, int *i);
int		token_parse_utils_heredoc(t_sh *sh, int *fd, const char *trigger);
int		token_globing_parse_utils_push_str(t_list *head, char *str);

int		token_parse_inhib(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_parse_bquote(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_parse_separator(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_parse_lbrace(void *target, t_parser *parser, t_lexer *lexer,
			int *i);
int		token_parse_rbrace(void *target, t_parser *parser, t_lexer *lexer,
			int *i);

int		token_globing_parse_none(void *target, t_parser *parser,
			t_lexer *lexer, int *i);
int		token_globing_parse_inhib(void *target, t_parser *parser,
			t_lexer *lexer, int *i);

#endif
