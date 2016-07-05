#include "shell.h"

static char				*s_set_prompt_quoting(int tokenid)
{
	if (tokenid == TC_QUOTE)
		return ("quote> ");
	else if (tokenid == TC_DQUOTE)
		return ("dquote> ");
	else if (tokenid == TC_PIPE)
		return ("pipe> ");
	else if (tokenid == TC_OR_IF)
		return ("cmdor> ");
	else if (tokenid == TC_AND_IF)
		return ("cmdand> ");
	else
		return ("> ");
}

static int				s_concat_new_input(char **cmd,
										t_termcaps_context *child_c,
										int tokenid,
										char **tmp)
{
	char				*buff_quote;

	buff_quote = NULL;
	if (tokenid == TC_BACKSLASH)
	{
		termcaps_string_to_command_line(1, "\0",
	 &child_c->command_line);
	}
	buff_quote = termcaps_read_input(child_c);
	if (ft_strcmp(buff_quote, "^C\n") == 0)
	{
		child_c->state = STATE_REGULAR;
		free(*tmp);
		ft_memdel((void **)&buff_quote);
		return (-1);
	}
	if ((*cmd = ft_strjoin(*tmp, buff_quote)) == NULL)
	{
		free(*tmp);
		ft_memdel((void **)&buff_quote);
		return (ST_MALLOC);
	}
	free(*tmp);
	ft_memdel((void **)&buff_quote);
	return (ST_OK);
}

static int				s_first_loop_check(char **cmd,
											t_termcaps_context *child_c,
											t_termcaps_context *c,
											int tokenid)
{
	size_t				command_str_size;
	char				command_str[TERMCAPS_BUFFER_MAX];
	char				*tmp;
	int					ret;

	ft_bzero(command_str, TERMCAPS_BUFFER_MAX);
	ASSERT(list_head__command_line_to_buffer(&c->command_line,
		(sizeof(command_str) - 1), &command_str_size, command_str));
	child_c->option = OPTION_QUOTING;
	(ft_strcmp(command_str, "\n") != 0) ? (tmp = ft_strjoin(command_str, "\n")):
		(tmp = ft_strdup(command_str));
	termcaps_string_to_command_line(ft_strlen(tmp), tmp,
	&c->command_line);
	if ((ret = s_concat_new_input(cmd, child_c, tokenid, &tmp)) != ST_OK)
		return (ret);
	return (ST_OK);
}

static int				s_qloop(t_termcaps_context *c,
								t_termcaps_context *child_context,
								char *cmd,
								int tokenid)
{
	char				*buff_quote;
	char				*tmp;
	int					ret;

	ret = 0;
	buff_quote = NULL;
	while ((parser(c->sh, cmd, F_PARSING_TERMCAPS, NULL)) != ST_OK)
	{
		(cmd[ft_strlen(cmd)-1] == '\n') ? (tmp = ft_strdup(cmd)) :
			(tmp = ft_strjoin(cmd, "\n"));
		termcaps_string_to_command_line(ft_strlen(cmd), cmd, &c->command_line);
		free(cmd);
		if ((ret = s_concat_new_input(&cmd, child_context, tokenid, &tmp))
			== ST_MALLOC)
			return (ST_MALLOC);
		else if (ret == -1)
			return (ST_OK);
	}
	list_head__command_line_destroy(&c->command_line);
	list_head__init(&c->command_line);
	termcaps_string_to_command_line((ft_strlen(cmd)), cmd, &c->command_line);
	return (ST_OK);
}

int						quoting_new_context(t_termcaps_context *context, int tokenid)
{
	t_termcaps_context	child_context;
	int					ret;
	char				*cmd;

	if (!(ret = 0) && context->option == OPTION_NONE)
	{
		termcaps_display_command_line(context);
		caps__print_cap(CAPS__DOWN, 0);
		termcaps_initialize(context->sh, s_set_prompt_quoting(tokenid),
							&child_context);
		if (s_first_loop_check(&cmd, &child_context, context, tokenid) == -1)
			return (ST_OK);
		if ((ret = s_qloop(context, &child_context, cmd, tokenid))
					!= ST_OK)
		{
			free(cmd);
			return (ret);
		}
		caps__delete_line(context->command_line.offset);
		caps__print_cap(CAPS__UP, 0);
		termcaps_finalize(&child_context);
		context->child = 1;
	}
	return (ret);
}
