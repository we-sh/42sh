#include "shell.h"
#include "builtin_set_local.h"

static int	s_builtin_export_set_local_and_env(t_sh **sh, char *envp_tmp)
{
	char	*value;
	char	*tmp;
	int		ret;
  int flag=0;
  t_var   *ptrvar;

  if ((tmp = ft_strdup(envp_tmp)) == NULL)
    return (ST_MALLOC);
  
  value = env_get_value_and_remove_equal_sign(tmp);
  ptrvar = (*sh)->local_vars;
  while (ptrvar)
  {
    if (ft_strcmp(ptrvar->key, tmp) == 0)
    {
      free(ptrvar->value);
      if (value)
      {
        if ((ptrvar->value = ft_strdup(value)) == NULL)
          return (ST_MALLOC);
      }
      flag = 1;
      break ;
    }
    ptrvar = ptrvar->next;
  }
  if (flag == 0)
  {
    if ((builtin_local_var_add(sh, tmp, value)) == ST_MALLOC)
      return (ST_MALLOC);
  }
  if (value && (ret = env_set(&(*sh)->envp, tmp, value)) != ST_OK)
		return (ret);
	free(tmp);
	return (ST_OK);
}

int			builtin_export_set(t_sh **sh, t_proc *p, int pos)
{
	int		ret;
  char  *value;
  char *argv;
  int i=0;
  t_var *ptrvar;

  ret = 0;
  ptrvar = (*sh)->local_vars;
  argv = ft_strdup(p->argv[pos]);
  log_debug("builtin_export");
  value = env_get_value_and_remove_equal_sign(argv);
  if (!value)
  {
    while (p->envp[i])
    {
      if (ft_strncmp(p->envp[i], argv, ft_strlen(argv)) == 0)
      {//AWD=ok export AWD && AWD= export AWD
  log_debug("builtin_export 1");
          if ((ret = s_builtin_export_set_local_and_env(sh,
                p->envp[i])) != ST_OK)
            return (ret);
          else
          {
            free(argv);
            return (ST_OK);
          }
      }
      i++;
    }
    while (ptrvar)
    {//TEST=1 ;export TEST
      if (ft_strcmp(ptrvar->key, argv) == 0)      
      {
        log_debug("builtin_export 2");
        if ((ret = env_set(&(*sh)->envp, argv, ptrvar->value)) != ST_OK)
          return (ret);
        else
        {
          free(argv);
          return (ST_OK);
        }
      }
      ptrvar = ptrvar->next;
    }
    if ((builtin_local_var_add(sh, argv, value)) == ST_MALLOC)
      return (ST_MALLOC);
    else
    {//export TEST
      free(argv);
      t_var *ptr;
      ptr = (*sh)->local_vars;
      while (ptr)
      {
        log_debug("ptr->key: %s, ptr->value:%s", ptr->key, ptr->value);
        ptr = ptr->next;
      }
      return (ST_OK);
    }
  }
  else
  {//export test=ok
    log_debug("builtin_export 3");

    if ((ret = s_builtin_export_set_local_and_env(sh,
          p->argv[pos])) != ST_OK)
      return (ret);
    else
    {
      free(argv);
      return (ST_OK);
    }
    if ((ret = env_set(&(*sh)->envp, argv, value)) != ST_OK)
      return (ret);
  }
  free(argv);
	return (ST_OK);
}