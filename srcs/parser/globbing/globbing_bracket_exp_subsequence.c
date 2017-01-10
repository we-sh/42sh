#include <shell.h>

static int			s_reverse_it(t_tmp **concat)
{
	char			ptr;
	char			*tmp_value;
	int				j;
	int				len;

	j = 0;
	ptr = 32;
	len = 127 - 32 - ft_strlen((*concat)->value);
	if ((tmp_value = (char *)malloc(sizeof(char) * len)) == NULL)
		return (ST_MALLOC);
	while (ptr < 127)
	{
		if (!ft_strchr((*concat)->value, ptr))
		{
			tmp_value[j] = ptr;
			j++;
		}
		ptr++;
	}
	tmp_value[j] = '\0';
	free((*concat)->value);
	if (((*concat)->value = ft_strdup(tmp_value)) == NULL)
		return (ST_MALLOC);
	free(tmp_value);
	return (ST_OK);
}

int					globbing_bracket_exp_subsequence(t_tmp **concat, int i)
{
	while ((*concat)->value[i] != '\0')
	{
		if (i + 2 < (int)ft_strlen((*concat)->value))
		{
			if ((*concat)->value[i + 1] == '-' &&
						((*concat)->value[i + 2]))
			{
				if ((globbing_before_expand(concat, i,
					ft_strlen((*concat)->value))) == ST_MALLOC)
					return (ST_MALLOC);
			}
		}
		if ((*concat)->value[i])
			i++;
	}
	if ((globbing_remove_double(concat)) == ST_MALLOC)
		return (ST_MALLOC);
	if ((*concat)->reverse == 1)
	{
		if ((s_reverse_it(concat)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}
