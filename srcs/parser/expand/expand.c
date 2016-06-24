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



/* -----------------------------------------------------------------
** to be exported */
int			token_parse_utils_get_word_and_inhib(char **content, t_lexer *lexer,
				int *i)
{
	char	*tmp;

	if ((*content = ft_strdup("")) == NULL)
		return (ST_MALLOC);
	while (*i < lexer->size && (TOKEN_TYPE(*i) == TT_INHIBITOR
								|| TOKEN_TYPE(*i) == TT_NAME))
	{
		if ((tmp = ft_strjoin(*content, TOKEN_CONTENT(*i))) == NULL)
			return (ST_MALLOC);
		free(*content);
		*content = tmp;
		(*i)++;
	}
	return (ST_OK);
}
/* ------------------------------------------------------------------ */

static void	s_free_argv(t_argv **argument)
{
	free((*argument)->buffer);
	free(*argument);
	*argument = NULL;
}

static char	*s_expand_escape_char_not_inhibited(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '\\')
			j++;
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
/*
static int	s_recursive(t_globing_param *params, t_lexer *lexer, int i)
{
	if (TOKEN_TYPE(*i) != TT_NAME && TOKEN_TYPE(*i) != TT_INHIBITOR)
		return (ST_OK);

	is_inhibited = 0;
	if (TOKEN_TYPE(*i) == TT_INHIBITOR)
	{
		is_inhibited = 1;
		(*i)++;
	}

	if (is_inhibited == 0)
	{
		if (params->depth == 1)
			if (expand_tilde(params, lexer, i) != ST_OK)
				return (ST_MALLOC);
	}

	if (is_inhibited == 1)
	{
		(*i)++;
	}

	params.depth++;
	return (s_recursive(params, p, lexer, i));
}
*/
int			expand(t_lexer *lexer, t_proc *p, int *i)
{
	int		ret;
	t_list	argv_list;
	char	*words;

	if ((ret = token_parse_utils_get_word_and_inhib(&words, lexer, i)) != ST_OK)
		return (ret);

	log_debug("word and inhibitors: `%s'", words);

	INIT_LIST_HEAD(&argv_list);
	ret = parser(lexer->sh, words, F_PARSING_GLOBING, &argv_list);
	if (ret != ST_OK)
		return (ret);

	free(words);
	log_debug("parser globing ret: %d", ret);

	t_argv	*argument;
	t_list	*pos;
	t_list	*safe;
	safe = argv_list.next;
	while ((pos = safe) && safe != &argv_list)
	{
		safe = safe->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		log_trace("argv string expanded: `%s'", argument->buffer);
		argument->buffer = s_expand_escape_char_not_inhibited(argument->buffer);
		if ((ft_array_push_back(&p->argv, argument->buffer)) < 0)
			return (ST_MALLOC);
		p->argc++;
		s_free_argv(&argument);
		//free(pos);
	}

	return (ST_OK);
}
