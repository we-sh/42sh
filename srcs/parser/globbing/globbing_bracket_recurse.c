#include "shell.h"

static int	s_is_total_make_sense(char *pattern)
{
	int		i;
	int		sign1;
	int		sign2;

	sign1 = 0;
	sign2 = 0;
	i = 0;
	while (pattern[i] != '\0')
	{
		if (pattern[i] == '[')
			sign1++;
		if (pattern[i] == ']')
			sign2++;
		i++;
	}
	if (sign1 == sign2)
		return (1);
	return (0);
}

static int	s_check_globbing_brack(char *pattern, char *input)
{
	char	*is_valid;

	is_valid = 0;
	if (!pattern || !input)
		return (0);
	if ((ft_strchr(pattern,'[') || ft_strchr(pattern, ']')))
	{
  		if ((is_valid = ft_strchr(pattern, '[')))
  			return (-1);
  		else if ((is_valid = ft_strchr(pattern, ']')))
  			return (-1);
		if (s_is_total_make_sense(pattern))
			return (-1);
	}
	if (*pattern == '?')
		return (*input && s_check_globbing_brack(pattern + 1, input + 1));
	else if (*pattern == '*')
		return (s_check_globbing_brack(pattern + 1, input) ||
				(*input && s_check_globbing_brack(pattern, input + 1)));
	else
		return (*input == *pattern++ && ((*input++ == '\0') ||
				s_check_globbing_brack(pattern, input)));
}

static int	s_sub(t_tmp *concat, char *sub_list, char *match, int i)
{
	int		ret;

	if ((ret = (s_check_globbing_brack(sub_list, match))) == 0)
	{
		free(sub_list);
		return (ST_OK);
	}
	else if (ret < 0) 
	{
		if (concat->value[i] != '*' && concat->value[i] != '?' &&
			!(ft_strchr(match, concat->value[i])))
		{
			free(sub_list);
			return (-1);
		}
	}
	else
	{
		free(sub_list);
		return ret;
	}
	return (ret);
}

int			globbing_bracket_recurse(t_mylist **list, t_tmp *concat, char *match, int i)
{
	int		j;
	int		ret;
	char	c[2];
	char	*sub_list;

	j = 0;
	c[0] = concat->value[i];
	c[1] = '\0';
	if ((sub_list = ft_strjoin3_safe(concat->before, c, concat->after)) == NULL)
		return (ST_MALLOC);
	if ((ret = s_sub(concat, sub_list, match, i)) >= 0)
		return (ret);
		if ((ret = (s_check_globbing_brack(sub_list, match))) == 0)
	{
		free(sub_list);
		return (ST_OK);
	}
	else if (ret < 0) 
	{
		if (concat->value[i] != '*' && concat->value[i] != '?' &&
			!(ft_strchr(match, concat->value[i])))
		{
			free(sub_list);
			return (-1);
		}
	}
	else
	{
		free(sub_list);
		return ret;
	}
	if ((globbing_bracket(list, sub_list, match)) == ST_MALLOC)
		return (ST_MALLOC);
	free(sub_list);
	return (ST_OK);
}

