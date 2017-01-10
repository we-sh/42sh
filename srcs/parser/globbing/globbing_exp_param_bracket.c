#include "shell.h"

// static int	s_add_new_arg(t_mylist **list, t_tmp *concat, char value_i)
// {
// 	char	*full;
// 	char	c[2];

// 	if (value_i)
// 	{
// 		c[0] = value_i;
// 		c[1] = '\0';		
// 	}
// 	if ((full = ft_strjoin3_safe(concat->before, c, concat->after)) == NULL)
// 		return (ST_MALLOC);
// 	if ((globbing_happend_to_list(list, full)) == ST_MALLOC)
// 		return (ST_MALLOC);
// 	free(full);
// 	return (ST_OK);
// }

// static int s_before_recurse(t_tmp *concat,
// 							t_mylist **list,
// 								char *match,
// 								int i)
// {
// 	int ret;

// 	if ((ret = globbing_bracket_recurse(list, concat, match, i)) != ST_OK)
// 	{
// 		if (ret == ST_MALLOC)
// 			return (ST_MALLOC);
// 		if ((s_add_new_arg(list, concat, concat->value[i])) == ST_MALLOC)
// 			return (ST_MALLOC);
// 		return (ST_OK);
// 	}
// 	else if (ret == -1)
// 	{
// 		if ((s_add_new_arg(list, concat, concat->value[i])) == ST_MALLOC)
// 			return (ST_MALLOC);
// 	}
// 	return (ST_OK);
// }

// static int s_set_beggin(t_tmp *concat, int *i)
// {
// 	if (concat->value[*i] == '^' && *i == 0 && concat->value[*i - 1] != '\\')
// 	{
// 		concat->reverse = 1;
// 		*i += 1;
// 	}
// 	if ((globbing_bracket_exp_subsequence(&concat, *i) == ST_MALLOC))
// 		return (ST_MALLOC);
// 	return (ST_OK);
// }

// int			globbing_exp_param_bracket(t_mylist **list,
// 										char *input,
// 										t_tmp *concat,
// 										char *match)
// {
// 	int		i;

// 	i = 0; 
// 	if (s_set_beggin(concat, &i) == ST_MALLOC)
// 		return (ST_MALLOC);
// 	while (concat->value[i] != '\0')
// 	{
// 		if (ft_strchr(match, concat->value[i]))
// 		{
// 			if (ft_strchr(input, '[') != NULL)
// 			{
// 				if (s_before_recurse(concat, list, match, i) == ST_MALLOC)
// 					return (ST_MALLOC);
// 				else
// 					break ;
// 			}
// 			else
// 			{
// 				if ((s_add_new_arg(list, concat, concat->value[i])) == ST_MALLOC)
// 					return (ST_MALLOC);
// 			}
// 		}
// 		i++;
// 	}
// 	return (ST_OK);
// }

static int s_add_new_arg(t_mylist **list, t_tmp *concat, char value_i)
{
	char *full;
	char c[2];

	if (value_i)
	{
		c[0] = value_i;
		c[1] = '\0';		
	}
	if ((full = ft_strjoin3_safe(concat->before, c, concat->after)) == NULL)
		return (ST_MALLOC);
	if ((globbing_happend_to_list(list, full)) == ST_MALLOC)
		return (ST_MALLOC);
	free(full);
	return (ST_OK);
}

static int s_is_total_make_sense(char *pattern)
{
	int i;
	int sign1;
	int sign2;

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

int	s_check_globbing_brack(char *pattern, char *input)
{
	char *is_valid;

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

int  globbing_bracket_recurse(t_mylist **list, t_tmp *concat, char *match, int i)
{
	int j;
	int ret;
	char c[2];
	char *sub_list;

	j = 0;
	c[0] = concat->value[i];
	c[1] = '\0';
	if ((sub_list = ft_strjoin3_safe(concat->before, c, concat->after)) == NULL)
		return (ST_MALLOC);
	if ((ret = (s_check_globbing_brack(sub_list, match))) == 0)
	{
		free(sub_list);
		return (ST_OK);
	}
	else if (ret == -1) 
	{
		if (concat->value[i] != '*' && concat->value[i] != '?' &&
			!(ft_strchr(match, concat->value[i])))
		{
			free(sub_list);
			return -1;
		}
	}
	else if (ret > 0)
	{
		free(sub_list);
		return ret;
	}
	if ((globbing_bracket(list, sub_list, match)) == ST_MALLOC)
		return (ST_MALLOC);
	free(sub_list);
	return (ST_OK);
}

int					globbing_exp_param_bracket(t_mylist **list,
													char *input,
													t_tmp *concat,
													char *match)
{
	int					i;
	int					ret;

	i = 0;
	ret = ST_OK;
	if (!concat->value)
		return (-1);
	if (concat->value[i] == '^' && i == 0)
	{
		concat->reverse = 1;
		i++;
	}
	if ((globbing_bracket_exp_subsequence(&concat, i) == ST_MALLOC))
		return (ST_MALLOC);
	while (concat->value[i] != '\0')
	{
		if (!ft_strchr(match, concat->value[i]))
			i++;
		else
		{
			if(ft_strchr(input, '[') != NULL)
			{
				if ((ret = globbing_bracket_recurse(list, concat, match, i)) != ST_OK)
				{
					if (ret == ST_MALLOC)
						return (ST_MALLOC);
					if ((s_add_new_arg(list, concat, concat->value[i])) == ST_MALLOC)
						return (ST_MALLOC);
					break ;
				}
				else if (ret == -1)
				{
					if ((s_add_new_arg(list, concat, concat->value[i])) == ST_MALLOC)
						return (ST_MALLOC);
					break ;
				}
			}
			else
			{
				if ((s_add_new_arg(list, concat, concat->value[i])) == ST_MALLOC)
					return (ST_MALLOC);
			}
			i++;
		}
	}
	return (ret);
}