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


// ----------------------------------------------------------------
// todo: to be exported to libft submodule
static int			ft_array_push_back(char ***array, char const *value)
{
	char	**new_array;
	size_t	total;

	if (!value || !array)
		return (-1);
	total = 0;
	if (*array)
		while ((*array)[total])
			total++;
	if ((new_array = (char **)malloc(sizeof(char *) * (total + 2))) == NULL)
		return (-1);
	total = 0;
	if (*array)
		while ((*array)[total])
		{
			if ((new_array[total] = ft_strdup((*array)[total])) == NULL)
				return (-1);
			total++;
		}
	if ((new_array[total] = ft_strdup(value)) == NULL)
		return (-1);
	new_array[total + 1] = NULL;
	ft_memdel_tab((void ***)&(*array));
	*array = new_array;
	return (total);
}
// ----------------------------------------------------------------

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

static int	s_recursive(t_proc *p, int i, char *(func)(char *))
{
	if (p->argv[i] == NULL)
		return (ST_OK);
	func(p->argv[i]);
	return (s_recursive(p, i + 1, func));
}

int			expand(t_proc *p, char *content, int is_inhibited)
{
	log_debug("exanding word: `%s`", content);
	if (is_inhibited == 0)
	{
		if ((content = expand_tilde(p, content)) == NULL)
			return (ST_MALLOC);
	}
	if (ft_array_push_back(&p->argv, content) < 0)
		return (ST_MALLOC);
	p->argc++;
	free(content);
	if (is_inhibited == 1)
		return (s_recursive(p, 0, &expand_escape_char));
	return (s_recursive(p, 0, &s_expand_escape_char_not_inhibited));
}
