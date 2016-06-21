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

static int				s_replace_backslash(t_termcaps_context *context)
{
	t_list_node_cmd	*node_cmd;
	t_list			*pos;

	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (node_cmd->character[0] == '\\')
		{
			node_cmd->character[0] = ' ';
			return (ST_OK);
		}
	}
	return (ST_OK);
}

static int				s_qloop(t_termcaps_context *c)
{
	char				*test;
	char				*buff_quote;
	t_termcaps_context	child_context;
	int 				ret = 0;

	s_d_init(c, &child_context);


	while ((ret = quoting_invalid(c)) != 0)
	{
		log_warn("INSIDE QLOOP");

		if (ret == 2)
		{
			log_info("TWO TWOT TWO");
			s_replace_backslash(c);
			g_in_child = 2;
		}


		buff_quote = termcaps_read_input(&child_context);
		if (s_check_pipe_case(c) == 1)
			termcaps_string_to_command_line((ft_strlen(buff_quote)),
											buff_quote,	&c->command_line);
		else
		{
			log_warn("ret != 2");
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
	int			ret;

	ret = quoting_invalid(context);
	if (g_in_child == 0 && (ret != 0))
	{
		if ((ret = s_qloop(context)) != ST_OK)
			return (ret);
	}
	return (ret);
}
