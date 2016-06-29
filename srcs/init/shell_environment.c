/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** -> if ((defaultenv[6] = ft_strjoin("LOGNAME=", getlogin())) == NULL)
** man 3 a verifier si seul moyen de le recuperer
*/

static char	**s_environment_default(void)
{
	char	**defaultenv;
	char	*tmp;

	if ((defaultenv = (char **)malloc(sizeof(char *) * 8)) == NULL)
		return (NULL);
	if ((defaultenv[0] = ft_strjoin("TERM=", env_get_term(NULL))) == NULL)
		return (NULL);
	if ((defaultenv[1] = ft_strjoin("PATH=", env_get_path(NULL))) == NULL)
		return (NULL);
	if ((defaultenv[2] = ft_strjoin("USER=", env_get_user(NULL))) == NULL)
		return (NULL);
	if ((defaultenv[3] = ft_strdup("SHLVL=1")) == NULL)
		return (NULL);
	if ((defaultenv[4] = ft_strjoin("HOME=", env_get_home(NULL))) == NULL)
		return (NULL);
	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (NULL);
	if ((defaultenv[5] = ft_strjoin("PWD=", tmp)) == NULL)
		return (NULL);
	free(tmp);
	if ((defaultenv[6] = ft_strjoin("LOGNAME=", getlogin())) == NULL)
		return (NULL);
	defaultenv[7] = NULL;
	return (defaultenv);
}

/*
** if ((sh->envp = s_environment_default()) == NULL)
**		return (ST_MALLOC);
**	return (ST_OK); // set default returm
*/

int			shell_environment(t_sh *sh, char **envp)
{
	int		i;

	i = 0;
	if (envp[i] == NULL)
	{
		if ((sh->envp = s_environment_default()) == NULL)
			return (ST_MALLOC);
		return (ST_OK);
	}
	while (envp[i])
		i++;
	if ((sh->envp = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (ST_MALLOC);
	i = 0;
	while (envp[i])
	{
		if ((sh->envp[i] = ft_strdup(envp[i])) == NULL)
			return (ST_MALLOC);
		i++;
	}
	sh->envp[i] = NULL;
	return (ST_OK);
}
