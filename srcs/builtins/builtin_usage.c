/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	builtin_usage(t_builtin const *bltin, int status)
{
	ft_printf("%r%s: %s: %s\n%s: %s\n",
		STDERR_FILENO,
		PROGRAM_NAME,
		bltin->name,
		i18n_translate(status),
		i18n_translate(ST_USAGE),
		bltin->usage);
}
