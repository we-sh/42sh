/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		job_background(t_sh *sh, t_job *j, int const sigcont)
{
	if (sigcont == 1)
		if (kill(-j->pgid, SIGCONT) < 0)
			return (job_kill(sh, j, ST_SIGCONT));
	job_set_stopped(j, 0);
	j->notified = 0;
	job_display_status(j, 1);
	return (ST_OK);
}
