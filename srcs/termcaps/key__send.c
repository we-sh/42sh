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

static void				s_reset_quoting(t_quoting *quoting)
{
	quoting->quote = 0;
	quoting->dbquote = 0;
	quoting->bkslash = 0;
	quoting->bkquote = 0;
}

static void				s_add_quoting(t_quoting **quoting, int buff)
{
	if (buff == 39)
		(*quoting)->quote += 1;
	else if (buff == 34)
		(*quoting)->dbquote += 1;
	else if (buff == 92)
		(*quoting)->bkslash += 1;
	else if (buff == 96)
		(*quoting)->bkquote += 1;
	// else
	// 	log_warn("Set_qutoing 0");
}


static int					s_quoting_invalid(t_quoting *quoting)
{
	if (quoting->quote % 2 != 0)
		return (1);
	else if (quoting->dbquote % 2 != 0)
		return (1);
	else if (quoting->bkquote % 2 != 0)
		return (1);
	if (quoting->bkslash > 0)
		return (1);
	return (0);
}

static int		s_set_quoting(t_quoting *quoting, t_termcaps_context *context)
{
	t_list_node_cmd *node_cmd;
	t_list *pos;

	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		s_add_quoting(&quoting, node_cmd->character[0]);
		//log_debug("value node_cmd->character[0] : %c", node_cmd->character[0]);
	}
	//	log_info("value quote : %d, value dbquote : %d, value kquote : %d, value bkslash : %d",
	//	(*quoting)->quote, (*quoting)->dbquote, (*quoting)->bkquote, (*quoting)->bkslash);
	//	quoting->quote, quoting->dbquote, quoting->bkquote, quoting->bkslash);
	return (0);
}

int				key__send(t_termcaps_context *context)
{
	char 		*tmp;
	char 		*buff_quote;
	int 		dontdisplay;

	tmp = NULL;
	dontdisplay = 0;
	buff_quote = NULL;
	
	log_success("INSIDE KEY SEND");

	// size_t		buffer_size;
	// char		buffer[2048];
	// char 		*buff_quote;

	// if (!list_head__command_line_to_buffer(&context->command_line,
	// 			sizeof(buffer) - 1, &buffer_size, buffer))
	// {
	// 	log_info("context->buff vide: %s", buffer);
	// 	return (0); //mettre un message d erreur
	// }
	//log_info("context->buff INIT -> %s", buffer);


	if (context->state == STATE_REGULAR)
	{

		s_set_quoting(&g_quot_status, context);
		if (s_quoting_invalid(&g_quot_status) == 1)
		{
			log_success("quoting NOT CLOSE!!!!!!!!!!");
			t_termcaps_context	child_context;



			termcaps_display_command_line(context->fd, &context->command_line);
			caps__print_cap(CAPS__DOWN, 0);
			termcaps_initialize(context->fd, "> ", &child_context);
			

			buff_quote = termcaps_read_input(&child_context);
			log_info("on a quoi dans buff ?? -> %s", buff_quote);
			termcaps_string_to_command_line((context->prompt.size + ft_strlen(buff_quote)),
											buff_quote,
											&context->command_line);
			free(buff_quote);
			log_info("on a quoi dans context->buff ?? -> %s", child_context.buffer);
			//termcaps_finalize(&child_context);
		dontdisplay = 1;
		}
		else
			log_warn("Quoting  CLOSE!!!!!!!!!!");


		if (termcaps_display_command_line(context->fd, &context->command_line))
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		else
		{
			log_error("minishell__display_command_line() failed");
			return (0);
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
	log_success("Send input !!!!!!!!!!");


	s_reset_quoting(&g_quot_status);

	return (1);
}
