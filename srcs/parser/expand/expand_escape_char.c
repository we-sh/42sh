#include "shell.h"


// -----------------------------------------------------
// export to libft ?
static int			ft_pow(int n, int exp)
{
	int				res;

	res = 1;
	while (exp-- > 0)
		res = res * n;
	return (res);
}
// ------------------------------------------------------


static void			s_digit(char *str, size_t *i, size_t *j)
{
	int				tmp;
	int				cnt;
	int				d;
	int				rem;

	tmp = ft_atoi(str + *i + 1);
	cnt = 0;
	d = 0;
	while (tmp > 0)
	{
		rem = tmp % 10;
		tmp = tmp / 10;
		d += rem * ft_pow(8, cnt);
		cnt++;
	}
	str[*j] = d;
	while (ft_isdigit(str[*i + 1]) == 1)
		(*i)++;
}

static void			s_not_digit(char *str, size_t *i, size_t *j)
{
	if (str[*i + 1] == 'a')
		str[*j] = '\a';
	else if (str[*i + 1] == 'b')
		str[*j] = '\b';
	else if (str[*i + 1] == 'f')
		str[*j] = '\f';
	else if (str[*i + 1] == 'n')
		str[*j] = '\n';
	else if (str[*i + 1] == 'r')
		str[*j] = '\r';
	else if (str[*i + 1] == 't')
		str[*j] = '\t';
	else if (str[*i + 1] == 'v')
		str[*j] = '\v';
	else if (str[*i + 1] == 92)
		str[*j] = 92;
	else if (str[*i + 1] == 39)
		str[*j] = 39;
	else if (str[*i + 1] == 34)
		str[*j] = 34;
	else if (str[*i + 1] == 63)
		str[*j] = 63;
	else
		(*i)--;
	(*i)++;
}

char				*expand_escape_char(char *str)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (ft_isdigit(str[i + 1]) == 1)
				s_digit(str, &i, &j);
			else
				s_not_digit(str, &i, &j);
		}
		else
		{
			str[j] = str[i];
		}
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
