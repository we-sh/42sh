#include "shell.h"

static int		s_is_inhibited(char *start, char *c)
{
	int		odd;

	odd = 0;
	while (c != start)
	{
		c--;
		if (c[0] != '\\')
			return (odd);
		odd = (odd == 0) ? 1 : 0;
	}
	return (odd);
}

static int		s_local_var_replace_out_of_loop(char *input, char **output,
												int i, int i2)
{
	if (i2 != i)
	{
		if (local_var_concat(output, input + i2, i - i2) != ST_OK)
			return (ST_MALLOC);
	}
	else if (i == 0)
	{
		if ((*output = ft_strnew(0)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

int				local_var_replace(t_sh *sh, char *in, char **out)
{
	int			i;
	int			i2;

	i = 0;
	i2 = 0;
	while (in[i])
	{
		if (in[i] == '$' && s_is_inhibited(in, in + i) == 0)
		{
			if (i2 != i)
			{
				if (local_var_concat(out, in + i2, i - i2) != ST_OK)
					return (ST_MALLOC);
			}
			if ((local_var_replace_char_or_loop(sh, in, out, &i)) != ST_OK)
				return (ST_MALLOC);
			i++;
			i2 = i;
		}
		else
			i++;
	}
	if ((s_local_var_replace_out_of_loop(in, out, i, i2)) == ST_MALLOC)
		return (ST_MALLOC);
	return (ST_OK);
}
