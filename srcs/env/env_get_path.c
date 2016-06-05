#include "shell.h"

/*
*  See "/etc/profile" 
*  (and so "/usr/libexec/path_helper -s") 
*  to retreive the default paths.
*/

char 			*env_get_path(char **envp)
{
	char			*tmp;
	uid_t			uid;

	if ((tmp = env_get(envp, "PATH")) == NULL)
	{
		uid = getuid();
		if (uid == 0)
			return (PATH_ROOT);
		else
			return (PATH_STD);
	}
	return (tmp);
}