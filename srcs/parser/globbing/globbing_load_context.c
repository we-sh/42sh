#include "shell.h"

static char	*s_get_l_ctx(char **arg, int is_root)
{
	char	*ptr;
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	if (!arg)
		return (NULL);
	if (is_root == 1)
		ret = ft_strdup("/");
	while (arg[i])
	{
		if (ft_strchr(arg[i], '*') == NULL && ft_strchr(arg[i], '?') == NULL)
		{
			ptr = ret;
			ret = ft_strjoin3_safe(ptr, arg[i], "/");
			if (ptr)
				ft_strdel(&ptr);
		}
		else
			return (ret);
		i++;
	}
	return (ret);
}

static char	*s_get_ctx(char **arg)
{
	int i;

	i = 0;
	if (!arg)
		return (NULL);
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

static char	*s_get_r_ctx(char **arg)
{
	char	*ret;
	int		token_detected;
	int		i;
	char	*ptr;

	if (!arg)
		return (NULL);
	ret = NULL;
	i = 0;
	token_detected = 0;
	while (arg[i])
	{
		if (token_detected == 1)
		{
			ptr = ret;
			ret = ft_strjoin3_safe(ptr, "/", arg[i]);
			if (ptr)
				ft_strdel(&ptr);
		}
		if (ft_strchr(arg[i], '*') != NULL || ft_strchr(arg[i], '?') != NULL)
			token_detected = 1;
		i++;
	}
	return (ret);
}

void		globbing_context_delete(t_ctx *ctx)
{
	if (ctx)
	{
		if (ctx->l)
			free(ctx->l);
		if (ctx->m)
			free(ctx->m);
		if (ctx->r)
			free(ctx->r);
		free(ctx);
	}
}

/*
** Fill a structure with the context of the variable:
** Example: ls ../../?ello/name
** Will produce:
** l_ctx: ../../
** m_ctx: ?ello
** r_ctx: /name
*/

int			globbing_load_context(t_ctx **ctx, char *arg)
{
	char	**sp;
	int		i;

	if (!(*ctx = ft_memalloc(sizeof(t_ctx))))
		return (ST_MALLOC);
	if (!arg)
		return (ST_EINVAL);
	if (!(sp = ft_strsplit(arg, '/')))
		return (ST_MALLOC);
	if (ft_strlen(arg) > 0 && arg[0] == '/')
		(*ctx)->l = s_get_l_ctx(sp, 1);
	else
		(*ctx)->l = s_get_l_ctx(sp, 0);
	(*ctx)->m = s_get_ctx(sp);
	(*ctx)->r = s_get_r_ctx(sp);
	i = 0;
	while (sp[i])
	{
		ft_strdel((&sp[i]));
		i++;
	}
	free(sp);
	sp = NULL;
	return (ST_OK);
}
