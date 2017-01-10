#include "shell.h"

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