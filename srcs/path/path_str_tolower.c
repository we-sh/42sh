#include "shell.h"

char		*path_str_tolower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower((int)str[i]);
		i++;
	}
	return (str);
}