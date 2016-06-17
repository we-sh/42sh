#include "parser.h"

int	token_parse_dbl_chev_right(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '>>'", "TT_REDIR");

	int	left_fd = 0;
	int	right_fd = 0;


	if (lexer->tokens[*i].code == TC_CHEV_RIGHT)
	{
		left_fd = STDOUT_FILENO;
	}
	else
	{
		int left = ft_atoi(lexer->tokens[*i].content);
		if (left == 0 || left == 1 || left == 2)
			left_fd = left;
		else
			log_error("bad file descriptor");
		(*i)++;
	}
	log_debug("%d", left_fd);
	(*i)++;

	


	if (lexer->tokens[*i].type == TT_SEPARATOR)
		(*i)++;

	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;

		int right = ft_atoi(lexer->tokens[*i].content);
		if (right == 0 || right == 1 || right == 2)
			right_fd = right;
		else
			log_error("bad file descriptor");

	}
	else
		right_fd = open(lexer->tokens[*i].content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	
	log_debug("fd to redirect : %d", right_fd);

	proc->stdout = right_fd;

	(*i)++;



	return (0);
}
