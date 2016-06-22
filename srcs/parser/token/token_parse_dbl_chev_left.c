#include "parser.h"

static int	s_open_heredoc(t_sh *sh, int *fd, const char *trigger)
{
	t_termcaps_context	termcaps_context;
	char				*buffer;
	int					pipefd[2];

	log_warn("trying to read_input for heredoc");

	if (pipe(pipefd) != 0)
		return (ST_PIPE);
	if (termcaps_initialize(sh, "> ", &termcaps_context) != ST_OK)
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
	}
	termcaps_finalize(&termcaps_context);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (ST_OK);
}

int	token_parse_dbl_chev_left(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '<<'", "TT_REDIR");

	if (parser->mode == F_PARSING_NONE)
	{
		int ret;
		char *content;
		(*i)++;
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
		return (ST_OK);
	}


	log_error("todo !!!");
	return (ST_OK);

	// todo: use parsing mode to customize what this function does
	(void)target;
	(void)parser;

	char *left = lexer->tokens[*i].content;
	(*i)++;
	if (lexer->tokens[*i].code != TC_CHEV_RIGHT)
		log_error("parsing in loosing state");
	(*i)++;

	if (ft_strcmp(lexer->tokens[*i].content, "&") == 0)
		(*i)++;

	char *right = lexer->tokens[*i].content;
	(*i)++;

	log_trace("extracting redire %s > %s", left, right);
	return (0);
}
