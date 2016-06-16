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

static int		s_is_quoting(t_termcaps_context *context)
{
	t_list_node_cmd *node_cmd;
	t_list *pos;


	log_info("INSIDE KEY SEND");

	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (node_cmd->character[0] == '\'')
		{
			return (1);
		}
		log_info("value 1 : %c", node_cmd->character[0]);
	}
	return (0);
}

int				key__send(t_termcaps_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		//GAB TODO




		if (s_is_quoting(context) == 1)
			log_info("quoting !!!!!!!!!!");
		else
			log_info(" NO quoting !!!!!!!!!!");
		// log_info("value 1 : %s", &context->command_line);
		// log_info("value 2 : %zu", &context->command_line.size);
		// log_info("value 2 : %zu", &context->command_line.offset);
		// log_info("diff : %zu", (&context->command_line.size - &context->command_line.offset));

		if (s_is_quoting(context) == 1)
		{
			t_termcaps_context	termcaps_context;

			termcaps_display_command_line(context->fd, &context->command_line);
			caps__print_cap(CAPS__DOWN, 0);
			termcaps_initialize(context->fd, "> ", &termcaps_context);
			while (s_is_quoting(context) == 1)
			{	
 		//	write(context->fd, "\n", 1);
				context->buffer = termcaps_read_input(&termcaps_context);
/*				termcaps_string_to_command_line(context->prompt.size,
  												context->prompt.bytes,
  												&context->command_line);
				string_to_command_line(&context->command_line);
*/			log_info(" %s", &context->buffer);
		//		&context->buffer
				free(context->buffer);
			}
 			termcaps_finalize(context);
		}






		if (!termcaps_display_command_line(context->fd, &context->command_line))
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
	return (1);
}
