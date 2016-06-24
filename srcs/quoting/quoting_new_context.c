#include "shell.h"

static int				s_d_init(t_termcaps_context *parent,
							t_termcaps_context *child)
{
	termcaps_display_command_line(parent);
	caps__print_cap(CAPS__DOWN, 0);
	termcaps_initialize(parent->sh, "> ", child);
	g_in_child = 1;
	return (ST_OK);
}

static int				s_d_end(t_termcaps_context *c, t_termcaps_context *ch)
{
	g_in_child = 0;
	caps__delete_line((*c).command_line.offset);
	caps__print_cap(CAPS__UP, 0);
//	free(ch->promptstr);
	termcaps_finalize(ch);
	g_child = 1;
	return (ST_OK);
}

// static int				s_check_pipe_case(t_termcaps_context *context)
// {
// 	t_list_node_cmd	*node_cmd;
// 	t_list			*pos;

// 	LIST_FOREACH(&context->command_line.list, pos)
// 	{
// 		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
// 		if (node_cmd->character[0] == '|')
// 			return (1);
// 	}
// 	return (ST_OK);
// }

// static int				s_replace_backslash(t_termcaps_context *context)
// {
// 	t_list_node_cmd	*node_cmd;
// 	t_list			*pos;

// 	LIST_FOREACH(&context->command_line.list, pos)
// 	{
// 		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
// 		if (node_cmd->character[0] == '\\')
// 		{
// 			node_cmd->character[0] = ' ';
// 			return (ST_OK);
// 		}
// 	}
// 	return (ST_OK);
// }

static int				s_qloop(t_termcaps_context *c, int quot_value)
{
	char				*test;
	char				*buff_quote;
	t_termcaps_context	child_context;
	int 				ret = 0;



	char *tmp;

	size_t				command_line_cur_size;
	char				command_line_cur[2048];



	(void)quot_value;
	s_d_init(c, &child_context);


	tmp = NULL;
	ft_bzero(command_line_cur, 2048);
	ASSERT(list_head__command_line_to_buffer(&c->command_line,
											sizeof(command_line_cur) - 1,
											&command_line_cur_size,
											command_line_cur));

	if (command_line_cur[0])
	 	tmp = ft_strdup(command_line_cur);
	log_warn("VALUE OF CHILD BUFFER  : %s", tmp);

	while ((parser(c->sh, tmp, F_PARSING_TERMCAPS, NULL)) != ST_OK)
	{
	log_success("should enter quoting context with token: %d", ret);

		buff_quote = termcaps_read_input(&child_context);

		log_warn("buff_quote Value : %s", buff_quote);

			if ((test = ft_strjoin("\n", buff_quote)) == NULL)
			{
				free(buff_quote);
				return (ST_MALLOC);
			}


			tmp = ft_strjoin(tmp, test);
			free(test);
		// }
		ft_memdel((void **)&buff_quote); //leaks du child_cntext ou autre i don't knowww
	}
	log_success("youyouyou ::::: %s", tmp);

	list_head__command_line_destroy(&c->command_line);
	list_head__init(&c->command_line);
	termcaps_string_to_command_line((ft_strlen(tmp)),
	 								tmp, &c->command_line);
	return (s_d_end(c, &child_context));
}

int						quoting_new_context(t_termcaps_context *context, int quot_value)
{
	int			ret;

	ret = 0;
	//ret = quoting_invalid(context);

	if (g_in_child == 0)// && (ret != 0))
	{
		if ((ret = s_qloop(context, quot_value)) != ST_OK)
			return (ret);
	}
	return (ret);
}
