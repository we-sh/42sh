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

int			expand(t_sh *sh, t_proc *p, char *content, int is_inhibited)
{
	log_debug("exanding word: `%s`", content);
	if (is_inhibited == 0)
	{
		if ((content = expand_tilde(sh, content)) == NULL)
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
