#include "shell.h"
#include "builtin_set_local.h"

static int	s_builtin_export_set_from_name(t_sh **sh, char *argv, char *value)
{
	char	*tmp;
	int		ret;

	if ((tmp = ft_strjoin3_safe(argv,"=",value)) == NULL)
		return (ST_MALLOC);
	if ((builtin_local_var_set_local_loop(sh, tmp)) == ST_MALLOC)
		return (ST_MALLOC);
	if ((ret = env_set(&(*sh)->envp, argv, value)) != ST_OK)
		return (ret);
	free(tmp);
	return (ST_OK);
}

static int	s_builtin_export_set_from_name_and_value(t_sh **sh, char *argv)
{
	char	*value;
	char	*tmp;
	int		ret;

	value = NULL;
	if ((tmp = ft_strdup(argv)) == NULL)
		return (ST_MALLOC);
	if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
	{
		if ((builtin_local_var_set_local_loop(sh, argv)) == ST_MALLOC)
			return (ST_MALLOC);
		if ((ret = env_set(&(*sh)->envp, tmp, value)) != ST_OK)
			return (ret);
	}
	free(tmp);
	return (ST_OK);
}

int			builtin_export_set(t_sh **sh, char *argv)
{
	char	*value;
	int		ret;

	ret = 0;
	if ((value = local_var_register(*sh, argv)) != NULL)
	{
		if ((ret = s_builtin_export_set_from_name(sh, argv, value)) != ST_OK)
			return (ret);
	}
	else
	{
		if ((ret = s_builtin_export_set_from_name_and_value(sh, argv)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}