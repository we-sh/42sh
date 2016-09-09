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
	else if (tokenid ==TC_BACKSLASH)
		return ("> ");
	else
		return ("> ");
}

static int				s_first_loop_check(char **cmd,
											t_termcaps_context *child_c,
											t_termcaps_context *c)
{
	size_t				command_str_size;
	char				command_str[TERMCAPS_BUFFER_MAX];
	char				*tmp;
	int					ret;

	ft_bzero(command_str, TERMCAPS_BUFFER_MAX);
	ASSERT(command_to_buffer(&c->command,
		(sizeof(command_str) - 1), &command_str_size, command_str));
	child_c->option = OPTION_QUOTING;
	(ft_strcmp(command_str, "\n") != 0) ? (tmp = ft_strjoin(command_str, "\n")):
		(tmp = ft_strdup(command_str));
	command_add_string(ft_strlen(tmp), tmp,
	&c->command);
	if ((ret = concat_new_input(cmd, child_c, &tmp)) == ST_MALLOC)
		return (ret);
	if (ret == -1)
	{
		command_clear(&child_c->command);
		command_clear(&c->command);
		command_add_string((ft_strlen(*cmd)), *cmd, &c->command);
		free(*cmd);
	}
	return (ret);
}

static int				s_qloop(char *cmd,
								t_termcaps_context *child_c,
								t_termcaps_context *c)
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
		command_add_string(ft_strlen(cmd), cmd, &c->command);
		free(cmd);
		if ((ret = concat_new_input(&cmd, child_c, &tmp))
			== ST_MALLOC)
			return (ST_MALLOC);
		if (ret == -1)
			break ;
	}
	command_clear(&c->command);
	command_add_string((ft_strlen(cmd)), cmd, &c->command);
	free(cmd);
	return (ST_OK);
}

int						quoting_new_context(t_termcaps_context *context, int tokenid)
{
	t_termcaps_context	child_context;
	int					ret;
	char				*cmd;

	if (!(ret = 0) && context->option == OPTION_NONE)
	{
		termcaps_display_command(context);
		caps__print_cap(CAPS__DOWN, 0);
		termcaps_initialize(context->sh, s_set_prompt_quoting(tokenid),
							&child_context);
		if ((ret = s_first_loop_check(&cmd, &child_context, context)) == ST_MALLOC)
			return (ST_MALLOC);
		if (ret != -1 && (ret = s_qloop(cmd, &child_context, context))
					!= ST_OK)
			return (ret);
		caps__delete_line(context->command.offset);
		caps__print_cap(CAPS__UP, 0);
		termcaps_finalize(&child_context);
		context->child = 1;
	}
	return (ret);
}
