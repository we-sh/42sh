#include "shell.h"
#include <dirent.h>

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
	ref_size = int_key_completion(context->sh->envp, buf, &matchs, &lookfor);
	if (list_is_empty(&matchs))
		return (1);
	if (list_size(&matchs) == 1)
		s_update_command(lookfor, &matchs, &context->command);
	else
		display_completion(context->fd, &matchs, ref_size);
	list_dir__destroy(&matchs);
	return (1);
}
