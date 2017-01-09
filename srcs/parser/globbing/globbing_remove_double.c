#include <shell.h>

int globbing_remove_double(t_tmp **concat)
{
	char	char_tab[127];
	int 	i;
	int 	j;
	int 	len;
	char 	*new_value;

	i = 0;
	j = 0;
	len = 0;
	ft_bzero(char_tab, 127);
	while ((*concat)->value[i])
	{
		char_tab[(int)(*concat)->value[i]] = 1;
		i++;
	}
	i = 0;
	while (i < 127)
	{
		if (char_tab[i] == 1)
			len++;
		i++;
	}
	ft_bzero(char_tab, 127);
	if ((new_value = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (ST_MALLOC);
	i = 0;
	while((*concat)->value[i])
	{
		if (char_tab[(int)(*concat)->value[i]] == 0)
		{
			new_value[j] = (*concat)->value[i];
			char_tab[(int)(*concat)->value[i]] = 1;
			j++;
		}
		i++;
	}
	new_value[j] = '\0';
	free((*concat)->value);
	if (((*concat)->value = ft_strdup(new_value)) == NULL)
		return (ST_MALLOC);
	free(new_value);
	return (ST_OK);
}