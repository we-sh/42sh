/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
*  See "/etc/profile"
*  (and so "/usr/libexec/path_helper -s")
*  to retreive the default paths.
*/

char				*env_get_path(char **envp)
{
	char			*tmp;
	uid_t			uid;

	tmp = env_get(envp, "PATH");
	if (!tmp || !tmp[0])
	{
		uid = getuid();
		if (uid == 0)
			return (PATH_RT);
		else
			return (PATH_STD);
	}
	return (tmp);
}
