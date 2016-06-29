/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		redir_free(t_redir **redir)
{
	if ((*redir)->fd > 0 && (*redir)->fd != STDIN_FILENO
		&& (*redir)->fd != STDOUT_FILENO && (*redir)->fd != STDERR_FILENO)
		close((*redir)->fd);
	ft_memdel((void **)redir);
}
