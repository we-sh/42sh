#include "shell.h"

#define HISTFILE				"HISTFILE"

#define HISTORY_FILENAME_SIZE	(sizeof(".wesh_history") - 1)
#define HISTORY_FILENAME				".wesh_history"

static int	s_history_histfile(char **envp, size_t size_max, char *filename)
{
	char	*histfile;
	size_t	size;

	histfile = env_get(envp, HISTFILE);
	if (histfile == NULL)
	{
		return (0);
	}
	size = ft_strlen(histfile);
	if (size >= size_max)
	{
		return (0);
	}
	ft_memcpy(filename, histfile, size);
	filename[size] = '\0';
	return (1);
}

static int	s_history_default(char **envp, size_t size_max, char *filename)
{
	char	*home;
	size_t	size;

	home = env_get_home(envp);
	if (home == NULL)
	{
		return (0);
	}
	size = ft_strlen(home);
	if (size + (sizeof("/") - 1) + HISTORY_FILENAME_SIZE > size_max)
	{
		return (0);
	}
	ft_memcpy(filename, home, size);
	filename[size] = '/';
	size += 1;
	ft_memcpy(filename + size, HISTORY_FILENAME, HISTORY_FILENAME_SIZE);
	filename[size + HISTORY_FILENAME_SIZE] = '\0';
	return (1);
}

int			history_get_filename(char **envp, size_t size_max, char *filename)
{
	if (s_history_histfile(envp, size_max, filename))
		return (1);
	if (s_history_default(envp, size_max, filename))
		return (1);
	return (0);
}
