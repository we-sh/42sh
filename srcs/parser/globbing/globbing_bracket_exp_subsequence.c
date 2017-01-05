#include <shell.h>

static char			*s_globbing_increment_range(unsigned char range_start, unsigned char range_end, int len)
{
	char			*new_value;
	char			tmp_start;
	int				j;

	j = 0;
	tmp_start = range_start;
	if ((new_value = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (tmp_start <= range_end)
	{
		if (tmp_start)
		{
			new_value[j] = tmp_start;
			j++;
		}
		tmp_start++;
	}
	new_value[j] = '\0';
	return (new_value);
}

static int s_remove_double(t_tmp **concat)
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
	return (ST_OK);
}

static int s_reverse_it(t_tmp **concat)
{
	char ptr;
	char *tmp_value;
	int j;
	int len;

	j = 0;
	ptr = 32;	
	len = ft_strlen((*concat)->value);
	len = 127 - 32 - len;
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

static int			s_globbing_expand_range(t_tmp **concat, int i, int *len)
{
	unsigned char	range_start;
	unsigned char	range_end;
	char 			*new_value;
	char 			*tmp_value;

	range_start = (*concat)->value[i];
	range_end = (*concat)->value[i + 2];
	*len = range_end - range_start;
	if (*len <= 0)
		return -1;
	else
	{
		if ((new_value = s_globbing_increment_range(range_start, range_end, *len)) == NULL)
			return (ST_MALLOC);
	}
	if (i > 0)
	{
		if ((tmp_value = ft_strnew(i)) == NULL)
			return (ST_MALLOC);
		tmp_value = ft_strncpy(tmp_value, (*concat)->value, i);
		free((*concat)->value);
		if (((*concat)->value = ft_strjoin(tmp_value, new_value)) == NULL)
			return (ST_MALLOC);
		free(tmp_value);
	}
	else
	{
		free((*concat)->value);
		if (((*concat)->value = ft_strdup(new_value)) == NULL)
			return (ST_MALLOC);
	}
	free(new_value);
	return (ST_OK);
}

int					globbing_bracket_exp_subsequence(t_tmp **concat, int i)
{
	char				*tmp_value_after_range;
	char				*tmp_concat_value;
	int					len;
	int					ret;

	len = ft_strlen((*concat)->value);
	while ((*concat)->value[i] != '\0')
	{
		if (i + 2 < len)
		{
			if ((*concat)->value[i+1] == '-' && 
						((*concat)->value[i+2])) // il y a une range
			{
				if ((tmp_value_after_range = ft_strdup((*concat)->value + i + 3)) == NULL)
					return (ST_MALLOC);
				if ((ret = s_globbing_expand_range(concat, i, &len)) != -1)
				{
					if (ret == ST_MALLOC)
						return (ST_MALLOC);
					if ((tmp_concat_value = ft_strdup((*concat)->value)) == NULL)
						return (ST_MALLOC);
					free((*concat)->value);
					if (((*concat)->value = ft_strjoin(tmp_concat_value , tmp_value_after_range)) == NULL)
						return (ST_MALLOC);
					free(tmp_concat_value);
					len = ft_strlen((*concat)->value);
					i += ret;
				}
				free(tmp_value_after_range);
			}
		}
		if ((*concat)->value[i])// && ft_isalnum((*concat)->value[i])) //Doit on check is allnum ?
			i++;
	}
	if ((s_remove_double(concat)) == ST_MALLOC)
		return (ST_MALLOC);
	if ((*concat)->reverse == 1)
	{
		if ((s_reverse_it(concat)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}
