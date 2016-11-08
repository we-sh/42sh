#include "shell.h"
#include "builtin_set_local.h"

static int	s_after(t_sh **sh, t_proc *p)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	while (p->argv[i])
	{
		if ((tmp = ft_strdup(p->argv[i])) == NULL)
			return (ST_MALLOC);
		if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
		{
			env_unset(&(*sh)->envp, tmp);
			builtin_local_var_delete(sh, tmp);
		}
		else
		{
			env_unset(&(*sh)->envp, p->argv[i]);
			builtin_local_var_delete(sh, tmp);
		}
		free(tmp);
		i++;
	}
	return (ST_OK);
}

int			builtin_template(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	(void)builtin;
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}
