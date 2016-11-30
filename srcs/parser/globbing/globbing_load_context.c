#include "shell.h"

/*
 * Y'a des leaks.
 */

static char	*s_get_left_ctx(char **arg, int is_root)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	if (is_root == 1)
		ret = ft_strdup("/");
	while (arg[i])
	{
		if (ft_strchr(arg[i], '*') == NULL && ft_strchr(arg[i], '?') == NULL)
		{
			if (ret == NULL)
				ret = ft_strdup(arg[i]);
			else
				ret = ft_strjoin(ret, arg[i]);
			ret = ft_strjoin(ret, "/");
		}
		else
		{
			return (ret);
		}
		i++;
	}
	return (ret);
}

static char	*s_get_ctx(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '*'))
			return (ft_strdup(arg[i]));
		if (ft_strchr(arg[i], '?'))
			return (ft_strdup(arg[i]));
		i++;
	}
	return (NULL);
}

static char	*s_get_right_ctx(char **arg)
{
	char	*ret;
	int		token_detected;
	int		i;

	if (!arg)
		return (NULL);
	ret = NULL;
	i = 0;
	token_detected = 0;
	while (arg[i])
	{
		if (token_detected == 1)
		{
			if (ret == NULL)
				ret = ft_strdup("/");
			else
				ret = ft_strjoin(ret, "/");
			ret = ft_strjoin(ret, arg[i]);
		}
		if (ft_strchr(arg[i], '*') != NULL || ft_strchr(arg[i], '?') != NULL)
			token_detected = 1;
		i++;
	}
	return (ret);
}

int			globbing_load_context(t_ctx **ctx, char *arg)
{
	char	**sp;

	if (!(*ctx = ft_memalloc(sizeof(t_ctx *))))
		return (ST_MALLOC);
	if (!arg)
		return (ST_EINVAL);
	if (!(sp = ft_strsplit(arg, '/')))
		return (ST_MALLOC);
	if (ft_strlen(arg) > 0 && arg[0] == '/')
		(*ctx)->left = s_get_left_ctx(sp, 1);
	else
		(*ctx)->left = s_get_left_ctx(sp, 0);
	(*ctx)->middle = s_get_ctx(sp);
	(*ctx)->right = s_get_right_ctx(sp);
	// delete array
	return (ST_OK);
}
