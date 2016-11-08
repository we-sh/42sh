#include "shell.h"

static char		*s_local_var_replace_loop(t_sh *sh, char *input, int *i)
{
	t_var		*ptr;
	int			pos;
	char		*tmp;

	pos = 0;
	ptr = sh->local_vars;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	if ((tmp = ft_strnew(pos)) == NULL)
		return (NULL);
	tmp = ft_strncpy(tmp, input, pos);
	*i = *i + pos;
	while (ptr)
	{
		if (ft_strcmp(tmp, ptr->key) == 0)
		{
			free(tmp);
			if (ptr->value)
				return (ft_strdup(ptr->value));
		}
		ptr = ptr->next;
	}
	return (ft_strnew(0));
}

int				s_concat_input_output(char **output, char *input, int len)
{
	int			old_len;
	char		*tmp;

	if (*output)
		old_len = ft_strlen(*output);
	else
		old_len = 0;
	tmp = *output;
	if ((*output = ft_strnew(old_len + len)) == NULL)
		return (ST_MALLOC);
	if (tmp)
		*output = ft_strcpy(*output, tmp);
	ft_strncpy(*output + old_len, input, len);
	if (tmp)
		free(tmp);
	return (ST_OK);
}

static int		s_local_var_replace_out_of_loop(char *input, char **output,
												int i, int i2)
{
	if (i2 != i)
	{
		if (s_concat_input_output(output, input + i2, i - i2) != ST_OK)
			return (ST_MALLOC);
	}
	else if (i == 0)
	{
		if ((*output = ft_strnew(0)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

static int		s_replace_char_or_loop(t_sh *sh, char *input,
										char **output, int *i)
{
	char		*tmp;
	int			ret;

	log_debug("BREAK 2.1");
	if (input[*i + 1] == '$' || input[*i + 1] == '?')
	{
		if (input[*i + 1] == '$')
			ret = sh->pgid;
		else
			ret = sh->last_exit_status;
		if ((tmp = ft_itoa(ret)) == NULL)
			return (ST_MALLOC);
		*i += 1;
	}
	else if ((tmp = s_local_var_replace_loop(sh, input + *i + 1, i)) == NULL)
		return (ST_MALLOC);
	log_debug("BREAK 2.2");
	if (s_concat_input_output(output, tmp, ft_strlen(tmp)) != ST_OK)
		return (ST_MALLOC);
	log_debug("BREAK 2.3");
	free(tmp);
	return (ST_OK);
}

int				local_var_replace(t_sh *sh, char *input, char **output)
{
	int			i;
	int			i2;

	i = 0;
	i2 = 0;
	log_debug("input: %s", input);
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (i2 != i)
			{
			log_debug("BREAK 1");
				if (s_concat_input_output(output, input + i2, i - i2) != ST_OK)
					return (ST_MALLOC);
			}
			log_debug("BREAK 2");
			if ((s_replace_char_or_loop(sh, input, output, &i)) != ST_OK)
				return (ST_MALLOC);
			i++;
			i2 = i;
			log_debug("BREAK 3");
		}
		else
			i++;
	}
	if ((s_local_var_replace_out_of_loop(input, output, i, i2)) == ST_MALLOC)
		return (ST_MALLOC);
	log_debug("OUT of local_var_replace");
	return (ST_OK);
}
