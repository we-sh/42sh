#include "shell.h"

static int	s_replace_tilde_with(t_argv *argument, char *str, int offset)
{
	char	*new_buffer;
	size_t	len;

	if (!str)
		return (ST_OK);
	len = ft_strlen(str);
	if ((new_buffer = (char *)malloc(sizeof(char) * (len
		+ ft_strlen(argument->buffer)))) == NULL)
		return (ST_MALLOC);
	ft_strcat(new_buffer, str);
	ft_strcat(new_buffer + len, argument->buffer + offset);
	free(argument->buffer);
	argument->buffer = new_buffer;
	return (ST_OK);
}

static int	s_process_pwd(t_sh *sh, t_argv *argument, t_argv *argument_next)
{
	if (argument->buffer[2] == '\0')
	{
		if (argument_next && argument_next->buffer
			&& argument_next->buffer[0] != '\0'
			&& argument_next->buffer[0] != '/')
			return (ST_OK);
	}
	else if (argument->buffer[2] != '/')
		return (ST_OK);
	if (argument->buffer[1] == '+')
		return (s_replace_tilde_with(argument, env_get(sh->envp, "PWD"), 2));
	return (s_replace_tilde_with(argument, env_get(sh->envp, "OLDPWD"), 2));
}

static int	s_process_user(t_sh *sh, t_argv *argument, t_argv *argument_next)
{
	(void)sh;
	(void)argument;
	(void)argument_next;
	return (ST_OK);
}

int			expand_tilde(t_sh *sh, t_list **argv_list)
{
	t_list	*pos;
	t_argv	*argument;
	t_argv	*argument_next;

	pos = (*argv_list)->next;
	if (pos == *argv_list)
		return (ST_OK);
	argument = CONTAINER_OF(pos, t_argv, argv_list);
	argument_next = NULL;
	if (pos->next != *argv_list)
		argument_next = CONTAINER_OF(pos->next, t_argv, argv_list);
	if (!(argument->buffer && argument->buffer[0] == '~'))
		return (ST_OK);
	if (argument->buffer[1] == '/')
		return (s_replace_tilde_with(argument, env_get_home(sh->envp), 1));
	if (argument->buffer[1] == '+' || argument->buffer[1] == '-')
		return (s_process_pwd(sh, argument, argument_next));
	return (s_process_user(sh, argument, argument_next));
}
