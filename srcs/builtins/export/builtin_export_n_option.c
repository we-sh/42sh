#include "shell.h"
#include "builtin_set_local.h"

int			builtin_export_n_option(t_sh **sh, char *argv)
{
	char	*value;
	char	*tmp;

	if ((tmp = ft_strdup(argv)) == NULL)
		return (ST_MALLOC);
	if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
	{
		if ((env_unset(&(*sh)->envp, tmp)) == ST_MALLOC)
			return (ST_MALLOC);
		builtin_local_var_delete(*sh, tmp);
	}
	else
	{
		if ((env_unset(&(*sh)->envp, tmp)) == ST_MALLOC)
			return (ST_MALLOC);
		builtin_local_var_delete(*sh, tmp);
	}
	free(tmp);
	return (ST_OK);
}
