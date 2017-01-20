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

static int		s_pass_command(const size_t command_size,
							t_buffer *buffer)
{
	int	lines;
	int	y_diff;

	lines = command_size / caps__win(WIN_COLUMNS);
	y_diff = 0;
	while (y_diff < (int)(command_size / caps__win(WIN_COLUMNS)))
	{
		ft_memcpy(buffer->bytes + buffer->size, NL, NL_SIZE);
		buffer->size += NL_SIZE;
		y_diff += 1;
	}
	return (y_diff);
}

static int		s_fill_buffer(const size_t command_size,
							t_list *head,
							const int ref_size,
							t_buffer *buffer)
{
	t_node_dir	*node_dir;
	t_list		*pos;
	int			y_diff;
	size_t		filename_count;
	size_t		filename_by_line;

	filename_by_line = caps__win(WIN_COLUMNS) / ref_size;
	y_diff = s_pass_command(command_size, buffer);
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
						node_dir->filename_size, node_dir->filename,
						buffer);
		filename_count += 1;
	}
	return (y_diff);
}

int				display_completion(const size_t command_size,
									const int fd,
									t_list *matchs,
									const int ref_size)
{
	size_t		list_dir_size;
	size_t		buffer_size_max;
	t_buffer	buffer;
	int			y_diff;

	list_dir_size = list_size(matchs);
	buffer_size_max = NL_SIZE + (ref_size + NL_SIZE) * list_dir_size;
	buffer.size = 0;
	buffer.bytes = (char *)malloc(buffer_size_max);
	ASSERT(buffer.bytes != NULL);
	y_diff = s_fill_buffer(command_size, matchs, ref_size, &buffer);
	if (!y_diff)
	{
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
