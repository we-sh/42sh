#include "shell.h"

static void			s_add_quoting(t_quoting *quoting, int buff)
{
	if (buff == 39)
		(*quoting).quote += 1;
	else if (buff == 34)
		(*quoting).dbquote += 1;
	else if (buff == 92)
		(*quoting).bkslash += 1;
	else if (buff == 96)
		(*quoting).bkquote += 1;
}

static void			s_add_quoting_pipe(t_quoting *quoting, int buff)
{
	if (buff == 124)
		(*quoting).pipe += 1;
}

static int			s_check_quoting_invalid(t_quoting *quoting)
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


int					quoting_invalid(t_termcaps_context *context,
									t_quoting quoting, int action)
{
	t_list_node_cmd	*node_cmd;
	t_list_node_cmd	*node_cmd_next;
	t_list			*pos;
	size_t		buffer_size;
	char		buffer[2048];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (0);
	}
	buffer[buffer_size] = '\0';

	char *tmp;

	if ((tmp = ft_strstr(buffer, "|")))
	{
		while (ft_isspace(*(++tmp)))
		;
		if (*tmp == '\0')
		{
			s_add_quoting_pipe(&quoting, '|');
			quoting.pipe = 1;
		}
	}


	LIST_FOREACH(&context->command_line.list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (pos->next != &context->command_line.list)
			node_cmd_next = CONTAINER_OF(pos->next, t_list_node_cmd, list);
		if (action == 0 && node_cmd->character[0] && quoting.pipe == 1)
			quoting.pipe = 0;
		else if (action == 0 && node_cmd->character[0] == '\\')
			quoting.bkquote = 0;
		else
			s_add_quoting(&quoting, node_cmd->character[0]);
	}
	return (s_check_quoting_invalid(&quoting));
}
