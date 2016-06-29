/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils_set_proc_fds.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	s_set_and_close(int *fd, int *fd_compare, int std, int new_fd)
{
	if (fd_compare)
		if (new_fd == std && *fd_compare == -1)
			new_fd = -1;
	if (*fd != STDIN_FILENO && *fd != STDOUT_FILENO && *fd != STDERR_FILENO)
		close(*fd);
	*fd = new_fd;
}

void		token_parse_utils_set_proc_fds(t_proc *p, int fd_l, int fd_r)
{
	if (!(fd_r == STDIN_FILENO
				&& (fd_l == STDOUT_FILENO || fd_l == STDERR_FILENO)))
	{
		if (fd_l == STDIN_FILENO)
		{
			s_set_and_close(&p->stdin, NULL, STDIN_FILENO, fd_r);
		}
		if (fd_l == STDOUT_FILENO)
		{
			s_set_and_close(&p->stdout, &p->stderr, STDERR_FILENO, fd_r);
		}
		if (fd_l == STDERR_FILENO)
		{
			s_set_and_close(&p->stderr, &p->stdout, STDOUT_FILENO, fd_r);
		}
	}
}
