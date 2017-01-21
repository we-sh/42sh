#include "shell.h"
#include "builtin_set_local.h"

int			builtin_export_set_local_and_env(t_sh **sh, char *envp_tmp)
{
	char	*value;
	char	*tmp;
	int		ret;

	if ((tmp = ft_strdup(envp_tmp)) == NULL)
		return (ST_MALLOC);
	value = env_get_value_and_remove_equal_sign(tmp);
	if ((builtin_export_update_local_with_value(sh, tmp, value)) != ST_OK)
		return (ST_MALLOC);
	if (value && (ret = env_set(&(*sh)->envp, tmp, value, HTABLE_MODIF)) != ST_OK)
		return (ret);
	free(tmp);
	return (ST_OK);
}
