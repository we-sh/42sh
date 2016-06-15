#include "parser.h"

/*
** These functions are able to apply an action on a specific token received.
** For example, the semi-column token, when it is detected, will return 1,
** which means for the parser that the job is finished.
** WARNING : the parameters should be unconsistent, or some are missing...
** WQRNING : this is one file per token...
*/

int	token_parse_none(t_node_job *job, char *token)
{
	char	*tmp;

	log_trace("entering token_parse_none");
	if (!(job->cmd))
		job->cmd = ft_strdup(token);
	else
	{
		tmp = ft_strjoin(job->cmd, token);
		free(job->cmd);
		job->cmd = tmp;
	}
	return (0);
}
