/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_user.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*env_get_user(char **envp)
{
	char			*tmp;
	uid_t			uid;
	struct passwd	*passwd;

	if ((tmp = env_get(envp, "USER")) == NULL)
	{
		uid = getuid();
		passwd = getpwuid(uid);
		return (passwd->pw_name);
	}
	return (tmp);
}
