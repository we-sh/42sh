#include "shell.h"

int			token_parse_utils_push_command(char *content, char **target)
{
	char	*tmp;

	tmp = *target;
	if ((*target = ft_strjoin(tmp, content)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	return (ST_OK);
}
