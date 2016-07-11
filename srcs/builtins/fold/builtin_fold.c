#include "shell.h"

static int	s_before(t_proc *p)
{
	int		width;

	if (p->bltin_status == ST_OK)
	{
		width = 80;
		if (option_is_set(&p->bltin_opt_head, ST_BLTIN_FOLD_OPT_W) == 1)
		{
			if ((width = ft_atoi(option_get_value(&p->bltin_opt_head,
												ST_BLTIN_FOLD_OPT_W))) < 1)
			{
				p->bltin_status = ST_BLTIN_FOLD_ERR_ILLEGALW;
				return (ST_OK);
			}
		}
		p->bltin_status = -width;
	}
	return (ST_OK);
}

static void	s_display_line(char *line, int width, int blank_character)
{
	int		pos_start;
	int		pos_cur;
	int		columns;
	char	character;
	int		i;

	(void)blank_character;
	pos_cur = 0;
	pos_start = 0;
	columns = 0;
	while ((character = line[pos_cur]) != '\0')
	{
		if (character == '\t')
			columns += 7;
		else if (character == '\b')
			columns -= columns > 0 ? 2 : 1;
		else if (character == '\r')
			columns = -1;
		columns++;
		if (columns > width)
		{
			if (pos_cur == 0)
				ft_putchar('\n');
			if (blank_character == 1)
			{
				i = pos_cur;
				while (i > pos_start && line[i - 1] != ' ')
					i--;
				if (i != pos_start)
				{
					pos_cur = i;
					character = line[pos_cur];
				}
			}
			if (pos_start != pos_cur)
			{
				line[pos_cur] = '\0';
				ft_putendl(line + pos_start);
				line[pos_cur] = character;
				pos_start = pos_cur;
				columns = 0;
				continue ;
			}
		}
		pos_cur++;
	}
	if (line[pos_start])
		ft_putstr(line + pos_start);
}

static int	s_process_read(int fd, int width, int blank_character)
{
	int		ret;
	int		loop_count;
	char	*line;

	loop_count = 0;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (loop_count > 0 && fd != STDIN_FILENO)
			ft_putchar('\n');
		s_display_line(line, width, blank_character);
		free(line);
		loop_count++;
		if (fd == STDIN_FILENO)
			ft_putchar('\n');
	}
	if (fd != STDIN_FILENO)
		ft_putchar('\n');
	if (fd != STDIN_FILENO)
		close(fd);
	if (ret < 0)
		return (ST_READ);
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	int		ret;
	int		errors;
	int		i;

	if (p->bltin_status > ST_OK)
	{
		if (p->bltin_status != ST_EINVAL)
			display_status(p->bltin_status, "fold", NULL);
		else
			builtin_usage(builtin, p->bltin_status);
		exit(EXIT_FAILURE);
	}
	errors = 0;
	i = 1;
	while (i < p->argc || p->argc == 1)
	{
		if ((ret = s_process_read(p->argc == 1 ? STDIN_FILENO : open(p->argv[i], O_RDONLY), -p->bltin_status,
				option_is_set(&p->bltin_opt_head, ST_BLTIN_FOLD_OPT_S))) != ST_OK)
		{
			errors++;
			display_status(ret, "fold", NULL);
		}
		if (p->argc == 1)
			break ;
		i++;
	}
	if (errors > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			builtin_fold(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (ST_OK);
	return (ST_OK);
}
