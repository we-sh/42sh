#include "shell.h"

static int				s_d_init(t_termcaps_context *c, t_termcaps_context *ch)
{
	termcaps_display_command_line(c);
	caps__print_cap(CAPS__DOWN, 0);
	termcaps_initialize(c->fd, "> ", ch);
	g_in_child = 1;
	return (ST_OK);
}

static int				s_d_end(t_termcaps_context *c, t_termcaps_context *ch)
{
	g_in_child = 0;
	caps__delete_line((*c).command_line.offset);
	caps__print_cap(CAPS__UP, 0);
	termcaps_finalize(ch);
	g_child = 1;
	return (ST_OK);
}

static int				s_check_pipe_case(t_termcaps_context *context)
{
	t_list_node_cmd	*node_cmd;
	t_list			*pos;

	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (node_cmd->character[0] == '|')
			return (1);
	}
	return (ST_OK);
}

static int				s_qloop(t_termcaps_context *c, t_quoting q, int a)
{
	char				*test;
	char				*buff_quote;
	t_termcaps_context	child_context;

	s_d_init(c, &child_context);
	while (quoting_invalid(c, q, a) == 1 && (a = 0) == 0)
	{
		buff_quote = termcaps_read_input(&child_context);
		if (s_check_pipe_case(c) == 1)
			termcaps_string_to_command_line((ft_strlen(buff_quote)),
											buff_quote,	&c->command_line);
		else
		{
			if ((test = ft_strjoin("\n", buff_quote)) == NULL)
			{
				free(buff_quote);
				return (ST_MALLOC);
			}
			termcaps_string_to_command_line((ft_strlen(test)),
											test, &c->command_line);
			free(test);
		}
		ft_memdel((void **)&buff_quote); //leaks du child_cntext ou autre i don't knowww
	}
	return (s_d_end(c, &child_context));
}

int						quoting_new_context(t_termcaps_context *context)
{
	int					action;
	t_quoting			quoting;

	quoting.quote = 0;
	quoting.dbquote = 0;
	quoting.bkquote = 0;
	quoting.bkslash = 0;
	quoting.pipe = 0;
	action = 1;
	if (g_in_child == 0 && quoting_invalid(context, quoting, action) == 1)
	{
		if ((s_qloop(context, quoting, action)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}
