#include <pwd.h>
#include "shell.h"

char				*env_get_home(char **envp)
{
	char			*tmp;
	uid_t			uid;
	struct passwd	*passwd;

	if ((tmp = env_get(envp, "HOME")) == NULL)
	{
		uid = getuid();
		if ((passwd = getpwuid(uid)) == NULL)
			return (NULL);
		free(tmp);
		return (passwd->pw_dir);
	}
	return (tmp);
}
