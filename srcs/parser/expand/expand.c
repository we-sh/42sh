#include "shell.h"

/*
** This function takes a string and perform expansions on it in
** the following order (as described here: http://pubs.opengroup.org/onlinep
** ubs/009604499/utilities/xcu_chap02.html#tag_02_06):
** 1. Tilde `~` expansion
** 2.
** 3.
** 4. Escape character `\`
*/

static int	s_list_argv_to_char_argv(t_proc *p, t_list *argv_list)
{
	t_argv	*argument;
	t_list	*pos;
	t_list	*safe;
	int		st;

	if ((st = globbing(&argv_list)) != ST_OK)
		return (st);
	safe = argv_list->next;
	while ((pos = safe) && safe != argv_list)
	{
		safe = safe->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		if ((ft_array_push_back(&p->argv, argument->buffer)) < 0)
			return (ST_MALLOC);
		p->argc++;
		free(argument->buffer);
		free(argument);
	}
	return (ST_OK);
}

int			expand(t_lexer *lexer, t_proc *p, int *i)
{
	int		ret;
	t_list	argv_list;
	char	*words;

	if ((ret = token_parse_utils_get_word_and_inhib(&words,
												lexer, i)) != ST_OK)
		return (ret);
	INIT_LIST_HEAD(&argv_list);
	ret = parser(lexer->sh, words, F_PARSING_GLOBING, &argv_list);
	if (ret != ST_OK)
		return (ret);
	free(words);
	if ((ret = s_list_argv_to_char_argv(p, &argv_list)) != ST_OK)
		return (ret);
	return (ST_OK);
}
