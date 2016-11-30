#include "shell.h"

int				local_var_concat_input_output(char **output, char *input, int len)
{
	int			old_len;
	char		*tmp;

	if (*output)
		old_len = ft_strlen(*output);
	else
		old_len = 0;
	tmp = *output;
	if ((*output = ft_strnew(old_len + len)) == NULL)
		return (ST_MALLOC);
	if (tmp)
		*output = ft_strcpy(*output, tmp);
	ft_strncpy(*output + old_len, input, len);
	if (tmp)
		free(tmp);
	return (ST_OK);
}
