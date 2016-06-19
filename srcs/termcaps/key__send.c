#include "shell.h"

static int		s_fill_context_buffer(t_termcaps_context *context, char *buffer)
{
	context->buffer = ft_strdup(buffer + context->prompt.size);
	if (!context->buffer)
		return (0);
	return (1);
}

static int		s_bufferize_input(t_termcaps_context *context)
{
	size_t		buffer_size;
	char		buffer[2048];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (0);
	}
	buffer[buffer_size] = '\0';
	if (!s_fill_context_buffer(context, buffer))
	{
		log_error("(s_fill_context_buffer() failed");
		return (0);
	}
	if (!key__share__command_line_to_history(context))
	{
		log_error("key__share__command_line_to_history() failed");
		return (0);
	}
	context->history.offset = context->history.size;
	return (1);
}

static void				s_add_quoting(t_quoting *quoting, int buff)
{
	if (buff == 39)
		quoting->quote += 1;
	else if (buff == 34)
		quoting->dbquote += 1;
	else if (buff == 92)
		quoting->bkslash += 1;
	else if (buff == 96)
		quoting->bkquote += 1;
	else if (buff == 124)
		quoting->pipe += 1;
	// else
	//	log_warn("Set_qutoing 0");
}


static int					s_check_quoting_invalid(t_quoting *quoting)
{
	if (quoting->quote % 2 != 0)
		return (1);
	else if (quoting->dbquote % 2 != 0)
		return (1);
	else if (quoting->bkquote % 2 != 0)
		return (1);
	if (quoting->bkslash > 0)
		return (1);
	if (quoting->pipe > 0)
		return (1);
	return (0);
}

static int		s_quoting_invalid(t_termcaps_context *context, t_quoting quoting, int action)
{
	t_list_node_cmd *node_cmd;
	t_list *pos;

	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (action == 0 && node_cmd->character[0] && quoting.pipe == 1) // check if it works with pipe
			quoting.pipe = 0;
		else if (action == 0 && node_cmd->character[0] == '\\')
			quoting.bkquote = 0;
		else
			s_add_quoting(&quoting, node_cmd->character[0]);
		log_debug("value node_cmd->character[0] : %c", node_cmd->character[0]);
	}
		log_info("value quote : %d, value dbquote : %d, value kquote : %d, value bkslash : %d, value pipe : %d",
		quoting.quote, quoting.dbquote, quoting.bkquote, quoting.bkslash, quoting.pipe);
	return (s_check_quoting_invalid(&quoting));
}

static char			*s_add_return_front_buff(char *buff_quote)
{
	int				size;
	char			*tmp;

	size = ft_strlen(buff_quote);
	tmp = ft_strjoin("\n", buff_quote);
	return (tmp);
}

int				key__send(t_termcaps_context *context)
{
	char		*buff_quote;
	int			action;
	char		*test;
	t_quoting	quoting = {
	.quote = 0,
	.dbquote = 0,
	.bkquote = 0,
	.bkslash = 0,
	.pipe = 0
	};

	test = NULL;
	buff_quote = NULL;
	action = 1;
	log_success("INSIDE KEY SEND");

	static int in_child = 0;
	int yoyoy_child = 0;


	if (context->state == STATE_REGULAR)
	{
		t_termcaps_context	child_context;

		if (in_child == 0 && s_quoting_invalid(context, quoting, action) == 1)
		{
				in_child = 1;
				log_success("quoting NOT CLOSE!!!!!!!!!!");

				termcaps_display_command_line(context->fd, &context->command_line);
				caps__print_cap(CAPS__DOWN, 0);
				termcaps_initialize(context->fd, "> ", &child_context);
				while (s_quoting_invalid(context, quoting, action) == 1)
				{
					buff_quote = termcaps_read_input(&child_context);
					test = s_add_return_front_buff(buff_quote);
						termcaps_string_to_command_line((ft_strlen(test)),
													test,
													&context->command_line);
					free(test);
					free(buff_quote);
					action = 0;
				}
				in_child = 0;
				caps__delete_line(context->command_line.offset);
				caps__print_cap(CAPS__UP, 0);
				log_warn("Quoting  CLOSE!!!!!!!!!!");

				log_info("on a quoi dans context->buff ?? -> %s", child_context.buffer);

				termcaps_finalize(&child_context);
				yoyoy_child = 1;
		}
		if (yoyoy_child == 0)
		{
			termcaps_display_command_line(context->fd, &context->command_line);
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		}
		if (context->command_line.size > context->prompt.size)
		{
			if (!s_bufferize_input(context))
			{
				log_error("s_bufferize_input() failed");
				return (0);
			}
		}
	}
	yoyoy_child = 0;
	log_success("Send input !!!!!!!!!!");
	return (1);
}
