#include "shell.h"

char				*quoting_add_return_front_buff(char *buff_quote)
{
	int				size;
	char			*tmp;
	int				i;
	int				j;

	if (!*buff_quote)
		return (NULL);
	i = 0;
	j = 1;
	size = ft_strlen(buff_quote);
	tmp = ft_strdup(buff_quote);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	tmp[0] = '\n';
	while (buff_quote[i] != '\0')
	{
		tmp[j] = buff_quote[i];
		i++;
		j++;
	}
	return (tmp);
}
