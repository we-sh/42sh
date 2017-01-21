#include "shell.h"
#include <dirent.h>

static int		s_replace_tilde(char *cmd, size_t cmd_size,
							const size_t size_max, char **envp)
{
	char	*home;
	size_t	home_size;
	char	*pt;
	size_t	pos;
	size_t	size_left;

	ASSERT(home = env_get_home(envp));
	home_size = ft_strlen(home);
	pt = cmd;
	while ((pt = ft_strchr(pt, '~')))
	{
		if (pt[1] == '/')
		{
			pos = pt - cmd;
			size_left = cmd_size - (pos + 2);
			ASSERT(pos + home_size + 1 + size_left <= size_max);
			ft_memmove(pt + home_size + 1, pt + 2, size_left);
			ft_memcpy(pt, home, home_size);
			pt[home_size] = '/';
			cmd_size += home_size - 2 + 1;
			cmd[cmd_size] = '\0';
		}
		pt++;
	}
	return (cmd_size);
}

static int		s_update_command(char *lookfor, t_list *matchs,
								t_list_head *command)
{
	t_node_dir	*node_dir;
	size_t		lookfor_size;

	lookfor_size = ft_strlen(lookfor);
	node_dir = CONTAINER_OF(matchs->next, t_node_dir, list);
	command_add_string(node_dir->filename_size - lookfor_size,
						node_dir->filename + lookfor_size,
						command);
	if (node_dir->d_type == DT_DIR)
		command_add_string(sizeof("/") - 1, "/", command);
	return (1);
}

extern int		key__completion(t_termcaps_context *context)
{
	size_t		buf_size;
	char		buf[1024];
	t_list		matchs;
	size_t		ref_size;
	char		*lookfor;

	ASSERT(command_to_buffer(&context->command,
				sizeof(buf) - 1, &buf_size, buf));
	buf_size -= context->prompt.size;
	ft_memmove(buf, buf + context->prompt.size, buf_size);
	buf[buf_size] = '\0';
	buf_size = s_replace_tilde(buf, buf_size, sizeof(buf) - 1,
								context->sh->envp);
	ASSERT(buf_size != 0);
	ref_size = int_key_completion(context->sh->envp, buf, &matchs, &lookfor);
	if (list_is_empty(&matchs))
		return (1);
	context->command.offset = context->command.size;
	if (list_size(&matchs) == 1)
		s_update_command(lookfor, &matchs, &context->command);
	else
		display_completion(context->command.size, context->fd,
							&matchs, ref_size);
	list_dir__destroy(&matchs);
	return (1);
}
