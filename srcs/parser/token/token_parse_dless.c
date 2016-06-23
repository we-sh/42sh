#include "parser.h"

static int	s_open_heredoc(t_sh *sh, int *fd, const char *trigger)
{
	t_termcaps_context	termcaps_context;
	char				*buffer;
	int					pipefd[2];

	if (pipe(pipefd) != 0)
		return (ST_PIPE);
	if (termcaps_initialize(sh, "heredoc> ", &termcaps_context) != 1)
		return (ST_TERMCAPS_INIT);
	while (1)
	{
		buffer = termcaps_read_input(&termcaps_context);
		if (!buffer)
			break ;
		if (!ft_strcmp(buffer, trigger))
		{
			free(buffer);
			break ;
		}
		ft_putendl_fd(buffer, pipefd[1]);
		free(buffer);
	}
	termcaps_finalize(&termcaps_context);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (ST_OK);
}

static int		s_fill_command(t_job *j, t_lexer *lexer, int *i)
{
	int					ret;
	char				*content;

	if (TOKEN_CODE(*i) != TC_DLESS)
	{
		token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
		(*i)++;
	}
	token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
	(*i)++;
	if (token_parse_utils_skip_separators(lexer, i, &j->command) != ST_OK)
		return (ST_MALLOC);
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		return (ret);
	token_parse_utils_push_command(content, &j->command);
	free(content);
	return (ST_OK);
}

static int		s_assign_fd_to_proc_stdin(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	t_list		*pos;
	t_redir		*r;
	char		*content;
	int			ret;

	if (TOKEN_CODE(*i) != TC_DLESS)
		(*i)++;
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
	{
		log_error("ret: %d", ret);
		return (ret);
	}
	free(content);
	if ((pos = parser->sh->redir_head.next) == &parser->sh->redir_head)
		return (ST_PARSER);
	r = CONTAINER_OF(pos, t_redir, list_redir);
	p->stdin = r->fd;
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	return (ST_OK);
}

int				token_parse_dless(void *target, t_parser *parser,
					t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '<<'", "TT_REDIR");

	int			ret;

	// set flag to avoid infinite loop with TC_NONE parser
	lexer->tokens[*i].is_redir_checked = 1;

	ret = ST_OK;
	if (parser->mode == F_PARSING_JOBS)
	{
		ret = s_fill_command((t_job *)target, lexer, i);
	}

	if (parser->mode == F_PARSING_NONE)
	{

		(*i)++;
		token_parse_utils_skip_separators(lexer, i, NULL);
		char *content;
		if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		{
			log_error("ret: %d", ret);
			return (ret);
		}

		log_warn("redir: %s", content);

		int fd;
		if ((ret = s_open_heredoc(parser->sh, &fd, content)) != ST_OK)
			return (ret);

		log_warn("redir: %s", content);

		t_redir *r;
		if ((r = redir_alloc(fd)) == NULL)
			return (ST_MALLOC);

		log_warn("alloc redir");

		list_push_back(&r->list_redir, &parser->sh->redir_head);

		log_warn("push redir");

		free(content);
		(*i)++;
	}

	if (parser->mode == F_PARSING_PROCS)
	{
		ret = s_assign_fd_to_proc_stdin((t_proc *)target, parser, lexer, i);
	}
	(*i)++;
	return (ret);
}
