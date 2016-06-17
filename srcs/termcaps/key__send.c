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
	else
		log_warn("Set_qutoing 0");
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
		log_info("value node_cmd->character[0] : %c", node_cmd->character[0]);
	}

	log_info("value quote : %d, value dbquote : %d, value kquote : %d, value bkslash : %d",
	//(*quoting)->quote, (*quoting)->dbquote, (*quoting)->bkquote, (*quoting)->bkslash);
	quoting->quote, quoting->dbquote, quoting->bkquote, quoting->bkslash);

	return (0);
}

int				key__send(t_termcaps_context *context)
{
	char 		*tmp;
	int 		dontdisplay;
	//t_quoting	*quot_status;

	tmp = NULL;
	dontdisplay = 0;
	log_success("INSIDE KEY SEND");

	size_t		buffer_size;
	char		buffer[2048];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
		return (0); //mettre un message d erreur
	log_info("context->buff INIT -> %s", buffer);
	//g_quot_status = s_init_quoting();
	if (context->state == STATE_REGULAR)
	{
		//GAB TODO
		// log_info("value 1 : %s", &context->command_line);
		// log_info("value 2 : %zu", &context->command_line.size);
		// log_info("value 2 : %zu", &context->command_line.offset);
		// log_info("diff : %zu", (&context->command_line.size - &context->command_line.offset));
		



		s_set_quoting(&g_quot_status, context);
		if (s_quoting_invalid(&g_quot_status) == 1)
		{
			log_success("quoting NOT CLOSE!!!!!!!!!!");
			t_termcaps_context	termcaps_context;

			termcaps_display_command_line(context->fd, &context->command_line);
			caps__print_cap(CAPS__DOWN, 0);
		

			termcaps_initialize(context->fd, "> ", &termcaps_context);
	//		while (s_quoting_invalid(&g_quot_status) == 1)
	//		{	
				char *buff;
				buff = termcaps_read_input(&termcaps_context);
				// termcaps_string_to_command_line(context->prompt.size,
				// 										context->prompt.bytes,
				// 										&context->command_line);
				// string_to_command_line(&context->command_line);
				log_info("on a quoi dans buff ?? -> %s", buff);
				// tmp = ft_strjoin(context->buffer, buff);
				// free(context->buffer);
				free(buff);
				// context->buffer = ft_strdup(tmp);
			//}

				if (termcaps_context.command_line.size > termcaps_context.prompt.size)
				{
					if (!s_bufferize_input(&termcaps_context))
					{
						log_error("s_bufferize_input() failed");
						return (0);
					}
				}
				log_info("on a quoi dans context->buff ?? -> %s", termcaps_context.buffer);

			log_success("Avant termcaps finalize");
				termcaps_finalize(&termcaps_context);
			log_success("Apres termcaps finalize");
			dontdisplay = 1;




		}
		else
		{
			log_warn("Quoting  CLOSE!!!!!!!!!!");
	//		caps__print_cap(CAPS__DOWN, 0);
		

		}






		if (dontdisplay != 1 && !termcaps_display_command_line(context->fd, &context->command_line))
		{
			log_error("minishell__display_command_line() failed");
			return (0);
		}
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
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

	return (1);
}
