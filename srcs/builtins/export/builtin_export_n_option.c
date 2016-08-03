#include "shell.h"

int			builtin_export_n_option(t_sh **sh, char *argv)
{
	char	*value;
	char	*tmp;
	
	if ((tmp = ft_strdup(argv)) == NULL)
		return (ST_MALLOC);
	if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
		env_unset(&(*sh)->envp, tmp);
	else
		env_unset(&(*sh)->envp, argv);
	free(tmp);
	return (ST_OK);
}