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
			return ("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
		else
			return ("/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games");
	}
	return (tmp);
}