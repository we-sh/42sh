#include "shell.h"

static char		*s_replace_from_local(t_var *ptr, char *tmp)
{
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
	return (NULL);
}

static char		*s_local_var_replace_loop(t_sh *sh, char *input, int *i)
{
	t_var		*ptr;
	int			pos;
	char		*tmp;
	char		*value;

	pos = 0;
	ptr = sh->local_vars;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	if ((tmp = ft_strnew(pos)) == NULL)
		return (NULL);
	tmp = ft_strncpy(tmp, input, pos);
	*i = *i + pos;
	if ((value = (s_replace_from_local(ptr, tmp))) != NULL)
		return (value);
	else if ((value = env_get(sh->envp, tmp)) != NULL)
	{
		free(tmp);
		return (ft_strdup(value));
	}
	free(tmp);
	return (ft_strnew(0));
}

int		local_var_replace_char_or_loop(t_sh *sh, char *input,
										char **output, int *i)
{
	char		*tmp;
	int			ret;

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
	if (local_var_concat(output, tmp, ft_strlen(tmp)) != ST_OK)
		return (ST_MALLOC);
	free(tmp);
	return (ST_OK);
}
