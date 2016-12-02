#include "shell.h"

int	count_func(const char *s, int (*test)(int c), int expected)
{
	int	i;

	i = 0;
	while (s[i] && test(s[i]) == expected)
		i++;
	return (i);
}
