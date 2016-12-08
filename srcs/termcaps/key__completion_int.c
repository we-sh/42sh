#include "shell.h"
#include <dirent.h>

static int		s_identify_lookfor(char *word, char **path, char **lookfor)
{
	int	word_size;
	int	i;

	word_size = ft_strlen(word);
	i = word_size;
	while (i-- >= 0)
		if (word[i] == '/')
			break ;
	if (i < 0)
	{
		i = 0;
		*path = "./";
		word[word_size] = '\0';
		*lookfor = word_size == 0 ? NULL : word;
	}
	else
	{
		i += 1;
		ft_memmove(word + i + 1, word + i, word_size - i);
		word[i] = '\0';
		word[word_size + 1] = '\0';
		*path = word;
		*lookfor = i == word_size ? NULL : word + i + 1;
	}
	return (1);
}

static int		s_is_separator(char c)
{
	return (ft_isspace(c) || c == '&' || c == '|' ||
			c == ';' || c == '"' || c == '\'');
}

static void		s_get_last_word(char *cmd, size_t *start, size_t *len)
{
	size_t	cmd_size;
	int		i;

	cmd_size = ft_strlen(cmd);
	i = cmd_size - 1;
	while (i >= 0)
	{
		if (s_is_separator(cmd[i]))
			break ;
		i--;
	}
	if (i < 0)
		i = 0;
	if (s_is_separator(cmd[i]))
		i += 1;
	*start = i;
	*len = cmd_size - i;
}

static int		s_is_binary(char *buf, size_t from, size_t from_len)
{
	size_t	start;
	size_t	len;
	char	c;
	int		i;

	if (ft_memchr(buf + from, '/', from_len))
		return (0);
	if (from == 0)
		return (1);
	from -= 1;
	c = buf[from];
	buf[from] = '\0';
	s_get_last_word(buf, &start, &len);
	if (ft_memchr(buf + start, '/', len) != NULL)
		return (0);
	buf[from] = c;
	i = from;
	while (i-- >= 0)
	{
		if (s_is_separator(buf[i]))
			break ;
		if (ft_isalnum(buf[i]))
			return (0);
	}
	return (1);
}

int				int_key_completion(char **envp, char *buf,
									t_list *matchs, char **lookfor)
{
	size_t		ref_size;
	size_t		start;
	size_t		len;
	int			is_binary;
	char		*path;

	s_get_last_word(buf, &start, &len);
	is_binary = s_is_binary(buf, start, len);
	ft_memmove(buf, buf + start, len);
	buf[len] = '\0';
	s_identify_lookfor(buf, &path, lookfor);
	ref_size = 0;
	INIT_LIST_HEAD(matchs);
	if (is_binary)
		match_binaries(envp, *lookfor, matchs, &ref_size);
	else
		get_matchs(path, *lookfor, matchs, &ref_size);
	return (ref_size + 2);
}
