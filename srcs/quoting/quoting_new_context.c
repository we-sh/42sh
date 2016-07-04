#include "shell.h"

static int				s_clean_loop(t_termcaps_context *c, char **final_input)
{
	list_head__command_line_destroy(&c->command_line);
	list_head__init(&c->command_line);
	termcaps_string_to_command_line((ft_strlen(*final_input)),
		*final_input, &c->command_line);
	free(*final_input);
	return (1);
}

static int				s_concat_new_input(char **final_input,
										t_termcaps_context *child_c,
										int tokenid,
										char **tmp)
{
	char				*buff_quote;

	buff_quote = NULL;
	if (tokenid == TC_BACKSLASH)
	{
		termcaps_string_to_command_line(1, " ",
	&child_c->command_line);
	}
	buff_quote = termcaps_read_input(child_c);
	if (ft_strcmp(buff_quote, "^C\n") == 0)
	{
		child_c->state = STATE_REGULAR;
		return (-1);
	}
	if ((*final_input = ft_strjoin(*tmp, buff_quote)) == NULL)
	{
		free(buff_quote);
		return (ST_MALLOC);
	}
	free(*tmp);
	ft_memdel((void **)&buff_quote);
	return (ST_OK);
}

static int				s_first_loop_check(char **final_input,
											t_termcaps_context *child_c,
											t_termcaps_context *c,
											int tokenid)
{
	size_t				command_str_size;
	char				command_str[TERMCAPS_BUFFER_MAX];
	char				*tmp;
	int					ret;

	ft_bzero(command_str, TERMCAPS_BUFFER_MAX);
	ASSERT(list_head__command_line_to_buffer(&c->command_line,
		(sizeof(command_str) - 1), &command_str_size, command_str));
	child_c->option = OPTION_QUOTING;
	tmp = ft_strjoin(command_str, "\n");
	termcaps_string_to_command_line(ft_strlen(tmp), tmp,
	&c->command_line);
	if ((ret = s_concat_new_input(final_input, child_c, tokenid, &tmp)) != ST_OK)
		return (ret);
	return (ST_OK);
}

static int				s_qloop(t_termcaps_context *c,
								t_termcaps_context *child_context,
								char *final_input, int tokenid)
{
	char				*buff_quote;
	char				*tmp;
	int					ret;

	ret = 0;
	if (s_first_loop_check(&final_input, child_context, c, tokenid) == -1)
		return (ST_OK);
	buff_quote = NULL;
	while ((ret = parser(c->sh, final_input, F_PARSING_TERMCAPS, NULL)) != ST_OK)
	{
		child_context->option = OPTION_QUOTING;	
		tmp = ft_strjoin(final_input, "\n");
		termcaps_string_to_command_line(ft_strlen(tmp), tmp,
		&c->command_line);
		if ((ret = s_concat_new_input(&final_input, child_context, tokenid, &tmp)) != ST_OK)
			return (ret);
	}
	s_clean_loop(c, &final_input);
	return (ST_OK);
}

int						quoting_new_context(t_termcaps_context *context, int tokenid)
{
	t_termcaps_context	child_context;
	int					ret;
	char				*final_input;

	final_input = NULL;
	ret = 0;
	if (context->option == OPTION_NONE)
	{
		termcaps_display_command_line(context);
		caps__print_cap(CAPS__DOWN, 0);
		termcaps_initialize(context->sh, "> ", &child_context);
		if ((ret = s_qloop(context, &child_context, final_input, tokenid)) != ST_OK)
			return (ret);
		caps__delete_line(context->command_line.offset);
		caps__print_cap(CAPS__UP, 0);
		termcaps_finalize(&child_context);
		context->child = 1;
	}
	return (ret);
}
