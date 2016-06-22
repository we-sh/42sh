
#include "shell.h"
#include <dirent.h>

#define ENDL_SIZE	(sizeof("\n") - 1)
#define ENDL				"\n"

static int		s_fill_buffer(t_list *head,
								const int ref_size,
								const size_t buffer_size_max,
								char *buffer)
{
	size_t		buffer_offset;
	size_t		filename_by_line;
	size_t		filename_count;
	t_node_dir	*node_dir;
	t_list		*pos;
	int			y_diff;
	t_list		*safe;

	y_diff = 0;
	filename_by_line = caps__win(WIN_COLUMNS) / ref_size;
	filename_count = 0;
	buffer_offset = 0;
	safe = head->next;
	while ((pos = safe) && (pos != head))
	{
		safe = safe->next;
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		ASSERT(buffer_offset + ref_size < buffer_size_max);
		if (filename_count++ % filename_by_line == 0)
		{
			ft_memcpy(buffer + buffer_offset, ENDL, ENDL_SIZE);
			buffer_offset += ENDL_SIZE;
			y_diff++;
		}
		ft_memcpy(buffer + buffer_offset, node_dir->filename.bytes,
			node_dir->filename.size);
		buffer_offset += node_dir->filename.size;
		ft_memset(buffer + buffer_offset, ' ',
			ref_size - node_dir->filename.size);
		buffer_offset += ref_size - node_dir->filename.size;
	}
	buffer[buffer_offset] = 0;
	return (y_diff);
}

static int		s_display_completion(t_list *head,
										const int fd,
										const int list_dir_size,
										const int ref_size)
{
	size_t		buffer_size_max;
	char		*buffer;
	int			y_diff;

	buffer_size_max = (ref_size + ENDL_SIZE) * list_dir_size;
	buffer = (char *)malloc(buffer_size_max);
	ASSERT(buffer != NULL);
	y_diff = s_fill_buffer(head, ref_size, buffer_size_max, buffer);
	if (!y_diff)
	{
		log_error("s_fill_buffer() failed");
		free(buffer);
		return (0);
	}
	termcaps_write(fd, buffer, ft_strlen(buffer));
	free(buffer);
	while (y_diff--)
		caps__print_cap(CAPS__UP, 0);
	caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	return (1);
}



int		key__completion(t_termcaps_context *context)
{
	t_buffer	match;
	t_list		head;
	size_t		ref_size;
	size_t		list_dir_size;
	t_node_dir	*node_dir;

	log_fatal("Yoooo entrer key_completion");
	ref_size = key__completion_list_dir(context, &head, &match) + 1;
	ASSERT(ref_size != 1);
	list_dir_size = list_size(&head);
	if (list_dir_size == 1)
	{
		node_dir = CONTAINER_OF(head.next, t_node_dir, list);
		termcaps_string_to_command_line(node_dir->filename.size - match.size,
										node_dir->filename.bytes + match.size,
										&context->command_line);
	}
	else
		s_display_completion(&head, context->fd, list_dir_size, ref_size);
	list_dir__destroy(&head);
	log_fatal("Yoooo sortit key_completion");
	return (1);
}
