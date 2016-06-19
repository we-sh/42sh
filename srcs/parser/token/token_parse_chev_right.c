#include "parser.h"

/*
** Case :
** echo tutu > tmp => [ 1 > open(tutu) ]
** ls 2>&1 1>/dev/null
** ls 1>1
** TODO generate error token
*/

int	token_parse_chev_right(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '>'", "TT_REDIR");

	int	fd_l;
	int	fd_r;

	fd_l = 0;
	fd_r = 0;

	// ls >...
	if (lexer->tokens[*i].code == TC_CHEV_RIGHT)
		fd_l = STDOUT_FILENO;
	else // ls 1>...
	{
		fd_l = ft_atoi(lexer->tokens[*i].content);
		if (fd_l != 0 && fd_l != 1 && fd_l != 2)
			log_error("bad file descriptor");
		(*i)++;
	}
	// go to redir
	(*i)++;

	// ls >&...
	if (lexer->tokens[*i].code == TC_AND)
	{
		(*i)++;
		// ls >&-
		if (ft_strcmp(lexer->tokens[*i].content, "-") == 0)
			fd_r = -1;
		else
		{
			// ls >&1
			log_debug(">&1");
			if ((ft_strisnumeric(lexer->tokens[*i].content)) == 0)
			{
				log_error("bad file descriptor");
				return (ST_PARSER);
			}
			else
			{
				fd_r = ft_atoi(lexer->tokens[*i].content);
				if (fd_r != 0 && fd_r != 1 && fd_r != 2)
					log_error("bad file descriptor");
			}
		}
	}
	else
	{
		// if separator, escape
		while (lexer->tokens[*i].type == TT_SEPARATOR)
			(*i)++;
		if (lexer->tokens[*i].code != TC_NONE)
		{
			log_error("parse error");
			return (ST_PARSER);
		}
		// ls > out
		fd_r = open(lexer->tokens[*i].content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}


	log_debug("fd left : %d - fd right : %d", fd_l, fd_r);

	if (!(fd_r == 0 && (fd_l == STDOUT_FILENO || fd_l == STDERR_FILENO)))
	{
		// to implement
		if (fd_l == 0)
			proc->stdin = fd_r;
		if (fd_l == 1)
			proc->stdout = fd_r;
		if (fd_l == 2)
			proc->stderr = fd_r;
	}

	(*i)++;

	return (0);
}
