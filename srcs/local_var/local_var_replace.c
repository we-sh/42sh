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
	log_debug("tmp ->'%s'", tmp);
	while (ptr)
	{
		if (ft_strcmp(tmp, ptr->key) == 0)
		{
			free(tmp);
			log_debug("2");
			return (ft_strdup(ptr->value));
		}
		ptr = ptr->next;
	}
	return (ft_strnew(0));
}

int				s_concat_input_output(char **output, char *input, int len)
{
	int 		old_len;
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
	log_debug("s_concat_input_output: *output '%s'", *output);
	if (tmp)
		free(tmp);
			log_debug("3");
	return (ST_OK);
}

//echo "    $test"
// i = 4
// i2 = 0
int				local_var_replace(t_sh *sh, char *input, char **output)
{
	int			i;
	int			i2;
	int			ret;
	char 		*tmp;

	i = 0;
	i2 = 0;
	while(input[i])
	{
		if (input[i] == '$')
		{
			if (i2 != i)
			{
				if (s_concat_input_output(output, input + i2, i - i2) != ST_OK)
					return (ST_MALLOC);
			}
			if (input[i+1] == '$' || input[i+1] == '?')
			{
				if (input[i+1] == '$')
					ret = sh->pgid;
				else
					ret = sh->last_exit_status;
				if((tmp = ft_itoa(ret)) == NULL)
					return (ST_MALLOC);
				i++;
			}
			else if ((tmp = s_local_var_replace_loop(sh, input + i + 1, &i)) == NULL)
				return (ST_MALLOC);
			log_debug("BEFORE local_var_replace : *output '%s'", *output);
			log_debug("before second concat_input tmp-> '%s'", tmp);
			if (s_concat_input_output(output, tmp, ft_strlen(tmp)) != ST_OK)
				return (ST_MALLOC);
			i++;
			log_debug("4");
			log_debug("AFTER local_var_replace: *output '%s'", *output);
			free(tmp);
			log_debug("5");
			i2 = i;
		}
		else
			i++;
	}
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