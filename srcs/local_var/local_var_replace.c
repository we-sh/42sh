#include "shell.h"

int		local_var_replace(char **argv, t_sh *sh)
{
	int	i;
	int	j;
	int	k;
	t_var	*ptr;
	char *tmp;

	ptr = sh->local_vars;
	i = 0;
	tmp = NULL;
	while (argv[i])
	{
		j = 0;
		k = 0;
		log_warn("Value of ARGV[%d] %s",i , argv[i]);
		while (argv[i][j] != '$' && argv[i][j] != '\0')
			j++;
		log_warn("Value of J %d et STRLEN %d",j , ft_strlen(argv[i]));
		if (j != (int)ft_strlen(argv[i]))
		{
			log_success("Go into j");
			while (ptr)
			{
				log_success("BROWSE PTR");
				if (j != 0 && ft_strcmp(argv[i] + j + 1, ptr->key) == 0)
				{
					tmp = (char *)malloc(sizeof(char) * (j + 1));
					while (k < j)
					{
						tmp[k] = argv[i][k];
						k++;
					}
					free(argv[i]);
					argv[i] = ft_strjoin(tmp, ptr->value);
					free(tmp);
					break ;
				}
				else
				{
					free(argv[i]);
					argv[i] = ft_strdup(ptr->value);
				}
				ptr = ptr->next;
			}
		}
		i++;
	}
	return (ST_OK);
}