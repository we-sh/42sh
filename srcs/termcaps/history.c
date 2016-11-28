#include "shell.h"

#define HISTORY_FILENAME_SIZE	(sizeof(".wesh_history") - 1)
#define HISTORY_FILENAME				".wesh_history"

int		history_filename(size_t size_max, char *filename)
{
	char		*home;
	size_t		size;

	home = env_get_home(NULL);
    log_debug("home {%s}", home);
	if (home == NULL)
	{
		log_error("getenv HOME failed");
		return (0);
	}
	size = ft_strlen(home);
	if (size + (sizeof("/") - 1) + HISTORY_FILENAME_SIZE >= size_max)
	{
		log_error("%s/%s: filename too long", home, HISTORY_FILENAME);
		return (0);
	}
	ft_memcpy(filename, home, size);
	filename[size++] = '/';
	ft_memcpy(filename + size, HISTORY_FILENAME, HISTORY_FILENAME_SIZE);
	size += HISTORY_FILENAME_SIZE;
	filename[size] = '\0';
    log_debug("history file {%s}", filename);
	return (1);
}

int		history_write(t_list_head *history, char *filename, int modified)
{
	int				fd;
	t_list			*pos;
	t_node_history	*node;
	size_t			size;
	int				flags;

    log_debug("writing history to {%s} only modified ? %s", filename, modified ? "true":"false");
	flags = O_CREAT | O_WRONLY;
    if (modified)
    {
        flags |= O_TRUNC;

        struct stat st;
        if (stat(filename, &st))
        {
            log_error("stat failed filename {%s}", filename);
            return (0);
        }
        size = st.st_size;
    }
	fd = open(filename, flags, 0666);
	if (fd == -1)
	{
		log_error("open: %s failed", filename);
		return (0);
	}
	size = 0;
	pos = &history->list;
	while ((pos = pos->next) && pos != &history->list)
	{
		node = CONTAINER_OF(pos, t_node_history, list);
        if (modified && !node->is_modified)
            continue ;
		if (!termcaps_write(fd, node->command.bytes, node->command.size) ||
			!termcaps_write(fd, "\n", sizeof("\n") - 1))
		{
			log_error("termcaps_write failed command {%.*s}", (int)node->command.size, node->command.bytes);
			close(fd);
			return (0);
		}
		size += node->command.size + sizeof("\n") - 1;
	}
    ftruncate(fd, size);
	close(fd);
	return (1);
}

int		history_init(t_termcaps_context *context)
{

    log_debug("Hello wold");
	INIT_LIST_HEAD(&context->history.list);
	context->history.size = 0;
	context->history.offset = 0;
	if (!history_filename(sizeof(context->history_file), context->history_file))
	{
		log_error("history_filename failed");
		return (0);
	}
	context->history_initial_size = 0;
	if (!history_load(context->history_file, &context->history, &context->history_initial_size))
	{
		log_error("history_load failed");
		return (0);
	}
	return (1);
}
