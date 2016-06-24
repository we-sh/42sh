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
	termcaps_finalize(ch);
	g_child = 1;
	return (ST_OK);
}

static int				s_first_loop_check(char **tmp2,
											t_termcaps_context *child_c,
											t_termcaps_context *c)
{
	char				*buff_quote;
	char				*tmp;
	size_t				command_str_size;
	char				command_str[2048];

	tmp = NULL;
	buff_quote = NULL;
	ft_bzero(command_str, 2048);
	ASSERT(list_head__command_line_to_buffer(&c->command_line,
											sizeof(command_str) - 1,
											&command_str_size,
											command_str));
	tmp = ft_strdup(command_str);
	buff_quote = termcaps_read_input(child_c);
	if (tmp)
	{
		if ((*tmp2 = ft_strjoin3_safe(tmp, "\n", buff_quote)) == NULL)
		{
			free(buff_quote);
			return (ST_MALLOC);
		}
		free(tmp);
		tmp = NULL;
	}
	return (ST_OK);
}

static int				s_qloop(t_termcaps_context *c,
								t_termcaps_context *child_context)
{
	char				*buff_quote;
	char				*tmp3;
	char				*tmp2;

	tmp2 = NULL;
	buff_quote = NULL;
	s_first_loop_check(&tmp2, child_context, c);
	while ((parser(context->sh, tmp2, F_PARSING_TERMCAPS, NULL)) != ST_OK)
	{
		buff_quote = termcaps_read_input(child_context);
		if ((tmp3 = ft_strjoin3_safe(tmp2, "\n", buff_quote)) == NULL)
		{
			free(buff_quote);
			return (ST_MALLOC);
		}
		free(tmp2);
		tmp2 = ft_strdup(tmp3);
		free(tmp3);
	}
	ft_memdel((void **)&buff_quote);
	list_head__command_line_destroy(&c->command_line);
	list_head__init(&c->command_line);
	termcaps_string_to_command_line((ft_strlen(tmp2)), tmp2, &c->command_line);
	free(tmp2);
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
		s_d_init(context, &child_context);
		if ((ret = s_qloop(context, &child_context)) != ST_OK)
			return (ret);
		s_d_end(context, &child_context);
	}
	return (ret);
}
