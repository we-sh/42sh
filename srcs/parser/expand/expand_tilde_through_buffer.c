#include <pwd.h>
#include "shell.h"

static int	s_replace_tilde_with(char **buffer, char *str, int offset)
{
	char	*new_buffer;
	size_t	len;

	if (str == NULL)
		return (ST_OK);
	len = ft_strlen(str);
	if ((new_buffer = ft_strnew(len + ft_strlen(*buffer))) == NULL)
		return (ST_MALLOC);
	ft_strcat(new_buffer, str);
	ft_strcat(new_buffer + len, (*buffer) + offset);
	free(*buffer);
	*buffer = new_buffer;
	return (ST_OK);
}

static int	s_process_pwd(t_sh *sh, char **buffer)
{
	if ((*buffer)[2] != '/' && (*buffer)[2] != '\0')
		return (ST_OK);
	if ((*buffer)[1] == '+')
		return (s_replace_tilde_with(buffer, env_get(sh->envp, "PWD"), 2));
	return (s_replace_tilde_with(buffer, env_get(sh->envp, "OLDPWD"), 2));
}

static int	s_process_user(char **buffer)
{
	char			*user;
	struct passwd	*passwd;
	size_t			len;

	len = 0;
	user = (*buffer) + 1;
	while (user[len] != '\0' && user[len] != '/')
		len++;
	if ((user = ft_strnew(len)) == NULL)
		return (ST_MALLOC);
	ft_strncat(user, (*buffer) + 1, len);
	passwd = getpwnam(user);
	free(user);
	if (passwd != NULL)
		return (s_replace_tilde_with(buffer, passwd->pw_dir, 1 + len));
	return (ST_OK);
}

int			expand_tilde_through_buffer(t_sh *sh, char **buffer)
{
	if (!(*buffer != NULL && (*buffer)[0] == '~'))
		return (ST_OK);
	if ((*buffer)[1] == '/' || (*buffer)[1] == '\0')
		return (s_replace_tilde_with(buffer, env_get_home(sh->envp), 1));
	if ((*buffer)[1] == '+' || (*buffer)[1] == '-')
		return (s_process_pwd(sh, buffer));
	return (s_process_user(buffer));
}
