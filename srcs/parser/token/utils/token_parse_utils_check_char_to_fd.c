#include "parser.h"

int	token_parse_utils_check_char_to_fd(char *f, int *fd)
{
	int	open_fd;

	if ((ft_strisnumeric(f)) == 0)
		return (ST_PARSER);
	else
	{
		open_fd = ft_atoi(f);
		if (open_fd != STDIN_FILENO && open_fd != STDOUT_FILENO
				&& open_fd != STDERR_FILENO)
			return (ST_PARSER);
		*fd = open_fd;
	}
	return (ST_OK);
}
