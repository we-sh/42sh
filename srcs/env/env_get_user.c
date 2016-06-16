#include "shell.h"

char				*env_get_user(char **envp)
{
	char			*tmp;
	uid_t			uid;
	struct passwd	*passwd;

	if ((tmp = env_get(envp, "USER")) == NULL)
	{
		uid = getuid();
		passwd = getpwuid(uid);
		return (passwd->pw_name);
	}
	return (tmp);
}
