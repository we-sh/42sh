#include "shell.h"

/*
** This function takes a string and perform expansions on it in
** the following order (as described here: http://pubs.opengroup.org/onlinep
** ubs/009604499/utilities/xcu_chap02.html#tag_02_06):
** 1. Tilde `~` expansion
** 2. Glob braces {...}
** 3. Globbing [...], ? and *
** 4. Escape character `\`
*/

static char	*s_expand_escape_char_not_inhibited(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '\\' && str[j + 1] == '\n')
			j += 2;
		else
		{
			if (str[j] == '\\')
				j++;
			str[i] = str[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

static int	s_list_argv_to_char_argv(t_proc *p, t_list *argv_list)
{
	t_argv	*argument;
	t_list	*pos;
	t_list	*safe;

	safe = argv_list->next;
	while ((pos = safe) && safe != argv_list)
	{
		safe = safe->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		if (argument->is_null == 0)
		{
			s_expand_escape_char_not_inhibited(argument->buffer);
			if ((ft_array_push_back(&p->argv, argument->buffer)) < 0)
				return (ST_MALLOC);
			p->argc++;
		}
		free(argument->buffer);
		free(argument);
	}
	return (ST_OK);
}

int			expand(t_lexer *lexer, t_proc *p, int *i)
{
	int		ret;
	t_list	*argv_list;
	char	*words;
	int		entry_token_type;

	entry_token_type = TOKEN_TYPE(*i);
	if ((argv_list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (ST_MALLOC);
	if ((ret = expand_get_words(&words, lexer, i)) != ST_OK)
		return (ret);
	INIT_LIST_HEAD(argv_list);
	if ((ret = parser(lexer->sh, words, F_PARSING_VAR, argv_list)) != ST_OK)
		return (ret);
	free(words);
	if (entry_token_type == TT_NAME
		&& (ret = expand_tilde(lexer->sh, &argv_list)) != ST_OK)
		return (ret);
	if ((ret = expand_glob_brace(lexer->sh, &argv_list)) != ST_OK)
		return (ret);
	if ((ret = globbing(&argv_list)) != ST_OK)
		return (ret);
	if ((ret = s_list_argv_to_char_argv(p, argv_list)) != ST_OK)
		return (ret);
	free(argv_list);
	return (ST_OK);
}
