#include "shell.h"
#include "libftprintf.h"

static void		s_print_node(t_node_history *node, size_t offset)
{
	ft_printf("%s %4d %.*s\n", node->is_modified ? "*" : " ",
			offset, (int)node->command.size, node->command.bytes);
}

void			default_history(t_list_head *history, char *arg)
{
	t_node_history	*node;
	t_list			*pos;
	size_t			offset;

	if (arg != NULL)
	{
		offset = ft_atoi(arg);
		if (offset == 0)
			return ;
		pos = list_nth(&history->list, offset);
		if (pos == &history->list)
			return ;
		node = CONTAINER_OF(pos, t_node_history, list);
		s_print_node(node, offset);
		return ;
	}
	offset = 1;
	pos = &history->list;
	while ((pos = pos->next) && pos != &history->list)
	{
		node = CONTAINER_OF(pos, t_node_history, list);
		s_print_node(node, offset);
		offset++;
	}
}
