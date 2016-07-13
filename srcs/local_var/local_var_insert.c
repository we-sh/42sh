#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the local variable struc if no binary are found.
*/

int local_var_insert(t_sh *sh, t_job **j)
{
	char **tab;

	log_warn("Value of job %s", (*j)->command);
	tab = ft_strplit((*j)->command);
	// while ((*envp)[i] != NULL)
	// {
	// 	log_info("Value of env[%d] : %s", i, (*envp)[i]);
	// 	i++;
	// }
	// i = 0;
	// log_info("Value ARGC : %d", *argc);
	
	// while ((*argv)[i] != NULL && (*argv)[i][0] != '\0' && (*argv)[i][0] != '=')
	// {
	// 	tmp = *argv[i];
	// 	if (path_hash_finder(*envp, &tmp) == ST_OK)
	// 	{
	// 		flag = 1;
	// 		log_success("IS a binary so add to env %s", tmp);
	// 	}
	// 	else
	// 		log_fatal("NOT a binary so add to env %s", tmp);
	// 	log_warn("POS: %d Value of ARGV[%d] : %s", pos, i, tmp);
	// 	i++;
	// }
}