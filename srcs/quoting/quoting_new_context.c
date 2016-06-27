#include "shell.h"

static int				s_first_loop_check(char **tmp2,
											t_termcaps_context *child_c,
											t_termcaps_context *c)
{
	char				*buff_quote;
	size_t				command_str_size;
	char				command_str[TERMCAPS_BUFFER_MAX];

	buff_quote = NULL;
	ft_bzero(command_str, TERMCAPS_BUFFER_MAX);
	ASSERT(list_head__command_line_to_buffer(&c->command_line,
		(sizeof(command_str) - 1), &command_str_size, command_str));
	child_c->state = STATE_QUOTING;
	buff_quote = termcaps_read_input(child_c);
	if (ft_strcmp(buff_quote, "^C\n") == 0)
	{
		child_c->state = STATE_REGULAR;
		return (-1);
	}
	if (command_str_size)
	{
		if ((*tmp2 = ft_strjoin3_safe(command_str, "\n", buff_quote)) == NULL)
		{
			free(buff_quote);
			return (ST_MALLOC);
		}
		free(buff_quote);
	}
	return (ST_OK);
}

static int				s_clean_loop(t_termcaps_context *c, char **tmp2)
{
	list_head__command_line_destroy(&c->command_line);
	list_head__init(&c->command_line);
	termcaps_string_to_command_line((ft_strlen(*tmp2)),
		*tmp2, &c->command_line);
	free(*tmp2);
	return (1);
}

static int				s_qloop(t_termcaps_context *c,
								t_termcaps_context *child_context)
{
	char				*buff_quote;
	char				*tmp3;
	char				*tmp2;

	tmp2 = NULL;
	if (s_first_loop_check(&tmp2, child_context, c) == -1)
		return (ST_OK);
	buff_quote = NULL;
	while ((parser(c->sh, tmp2, F_PARSING_TERMCAPS, NULL)) != ST_OK)
	{
		child_context->state = STATE_QUOTING;
		buff_quote = termcaps_read_input(child_context);
		if (ft_strcmp(buff_quote, "^C\n") == 0)
		{
			c->state = STATE_REGULAR;
			return (ST_OK);
		}
		if ((tmp3 = ft_strjoin3_safe(tmp2, "\n", buff_quote)) == NULL)
		{
			free(buff_quote);
			return (ST_MALLOC);
		}
		free(tmp2);
		tmp2 = ft_strdup(tmp3);
		free(tmp3);
		ft_memdel((void **)&buff_quote);
	}
	s_clean_loop(c, &tmp2);
	return (ST_OK);
}

int						quoting_new_context(t_termcaps_context *context,
											int quot_value)
{
	t_termcaps_context	child_context;
	int					ret;

	ret = 0;
	(void)quot_value;
	if (g_in_child == 0)
	{
		termcaps_display_command_line(context);
		caps__print_cap(CAPS__DOWN, 0);
		termcaps_initialize(context->sh, "> ", &child_context);
		g_in_child = 1;
		if ((ret = s_qloop(context, &child_context)) != ST_OK)
			return (ret);
		g_in_child = 0;
		caps__delete_line(context->command_line.offset);
		caps__print_cap(CAPS__UP, 0);
		termcaps_finalize(&child_context);
		g_child = 1;
	}
	return (ret);
}
