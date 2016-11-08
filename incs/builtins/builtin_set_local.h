#ifndef BUILTIN_SET_LOCAL_H
# define BUILTIN_SET_LOCAL_H

# include "builtin.h"

int		builtin_local_var_update(t_var **ptrvar, char *value);
int		builtin_local_var_add(t_sh **sh, char *key, char *value);
int		builtin_local_var_set_local_loop(t_sh **sh, char *key, char *value);
int		builtin_local_var_delete(t_sh **sh, char *key);
int		builtin_export_n_option(t_sh **sh, char *argv);
int		builtin_export_set(t_sh **sh, t_proc *p, int pos);
int		builtin_export_set_with_no_value(t_sh **sh, t_proc *p, char *value,
										char *argv);
int		builtin_export_update_local_with_value(t_sh **sh, char *argv,
										char *value);
int		builtin_export_set_local_and_env(t_sh **sh, char *envp_tmp);

static const t_builtin		g_builtin_set_local = {
	.index = BLTIN_SET_LOCAL,
	.name = "setlocal",
	.usage = "setlocal [VAR=[VALUE]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_SET_LOCAL,
	.exe = &builtin_set_local,
	.options = NULL
};

#endif
