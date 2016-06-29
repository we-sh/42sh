/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_kill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	job_kill(t_sh *sh, t_job *j, int status)
{
	if (j->pgid != 0)
	{
		kill(-j->pgid, SIGTERM);
		kill(-j->pgid, SIGCONT);
	}
	j->notified = 1;
	if (ioctl(sh->fd, TIOCSPGRP, &sh->pgid) == -1)
	{
		if (status != ST_OK)
			status = ST_TCSETPGRP;
	}
	return (status);
}
