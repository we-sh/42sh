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

static int			s_check_quoting_invalid(t_quoting quoting)
{
	if (quoting.quote % 2 != 0)
		return (1);
	else if (quoting.dbquote % 2 != 0)
		return (1);
	else if (quoting.bkquote % 2 != 0)
		return (1);
	if (quoting.bkslash > 0)
		return (2);
	if (quoting.pipe > 0)
		return (1);
	return (0);
}

int					quoting_invalid(t_termcaps_context *context)
{
	t_quoting			quoting;
	size_t		buffer_size;
	char		buffer[2048];
	int i =0 ;
	int j = 0;

	quoting.quote = 0;
	quoting.dbquote = 0;
	quoting.bkquote = 0;
	quoting.bkslash = 0;
	quoting.pipe = 0;
	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (0);
	}
	buffer[buffer_size] = '\0';

	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			j = i + 1;
			while (ft_isspace((buffer[j])))
				j++;
			if (buffer[j] == '\0')
				s_add_quoting_pipe(&quoting, '|');
		}
		else
			s_add_quoting(&quoting, buffer[i]);
		i++;
	}
	log_success("quoting.bkslash = %d", quoting.bkslash);
	return (s_check_quoting_invalid(quoting));
}
