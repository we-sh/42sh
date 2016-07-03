#include "shell.h"
#include <dirent.h>

#define NL_SIZE	(sizeof("\n") - 1)
#define NL				"\n"

static void		s_concat_buffer(size_t ref_size,
								size_t filename_size,
								char *filename,
								t_buffer *buffer)
{
	ft_memcpy(buffer->bytes + buffer->size,
			  filename,
			  filename_size);
	buffer->size += filename_size;
	ft_memset(buffer->bytes + buffer->size, ' ',
			  ref_size - filename_size);
	buffer->size += ref_size - filename_size;
}

static int		s_fill_buffer(t_list *head,
							  const int ref_size,
							  t_buffer *buffer)
{
	t_node_dir	*node_dir;
	t_list		*pos;
	int			y_diff;
	size_t		filename_count;
	size_t		filename_by_line;

	filename_by_line = caps__win(WIN_COLUMNS) / ref_size;
	y_diff = 0;
	filename_count = 0;
	pos = head;
	while ((pos = pos->next) && (pos != head))
	{
		if (filename_count % filename_by_line == 0)
		{
			ft_memcpy(buffer->bytes + buffer->size, NL, NL_SIZE);
			buffer->size += NL_SIZE;
			y_diff += 1;
		}
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		s_concat_buffer(ref_size,
						node_dir->filename_size,
						node_dir->filename,
						buffer);
		filename_count += 1;
	}
	return (y_diff);
}

static int		s_display_completion(t_list *head,
										const int fd,
										const int list_dir_size,
										const int ref_size)
{
	size_t		buffer_size_max;
	t_buffer	buffer;
	int			y_diff;

	buffer_size_max = NL_SIZE + (ref_size + NL_SIZE) * list_dir_size;
	buffer.size = 0;
	buffer.bytes = (char *)malloc(buffer_size_max);
	ASSERT(buffer.bytes != NULL);
	y_diff = s_fill_buffer(head, ref_size, &buffer);
	if (!y_diff)
	{
		log_error("s_fill_buffer() failed");
		free(buffer.bytes);
		return (0);
	}
	termcaps_write(fd, buffer.bytes, buffer.size);
	free(buffer.bytes);
	while (y_diff--)
		caps__print_cap(CAPS__UP, 0);
	caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	return (1);
}

int				key__completion(t_termcaps_context *context)
{
	t_buffer	match;
	t_list		head;
	size_t		ref_size;
	size_t		list_dir_size;
	t_node_dir	*node_dir;

	ref_size = key__completion_list_dir(context, &head, &match) + 1;
	ASSERT(ref_size);
	list_dir_size = list_size(&head);
	if (list_dir_size == 1)
	{
		node_dir = CONTAINER_OF(head.next, t_node_dir, list);
		termcaps_string_to_command_line(node_dir->filename_size - match.size,
										node_dir->filename + match.size,
										&context->command_line);
		if (node_dir->d_type == DT_DIR)
			termcaps_string_to_command_line(sizeof ("/") - 1, "/", &context->command_line);
	}
	else
	{
		s_display_completion(&head, context->fd, list_dir_size, ref_size);
	}
	list_dir__destroy(&head);
	return (1);
}
