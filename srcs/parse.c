#include "shell.h"

static int	redirection_chevr_right(t_proc *proc, const char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ST_OPEN);
	proc->stdout = fd;
	return (ST_OK);
}

static int	redirection_dbl_chevr_right(t_proc *proc, const char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ST_OPEN);
	proc->stdout = fd;
	return (ST_OK);
}

static int	redirection_chevr_left(t_proc *proc, const char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (ST_OPEN);
	proc->stdin = fd;
	return (ST_OK);
}

static int	redirection_dbl_chevr_left(t_proc *proc, const char *trigger)
{
	t_termcaps_context	termcaps_context;
	char				*buffer;
	int					pipefd[2];

	if (pipe(pipefd) != 0)
		return (ST_PIPE);
	if (!termcaps_initialize(0, "> ", &termcaps_context))
		return (ST_TERMCAPS_INIT);
	while (1)
	{
		buffer = termcaps_read_input(&termcaps_context);
		if (!buffer)
			break ;
		if (!ft_strcmp(buffer, trigger))
		{
			free(buffer);
			break ;
		}
		ft_putendl_fd(buffer, pipefd[1]);
	}
	termcaps_finalize(&termcaps_context);
	close(pipefd[1]);
	proc->stdin = pipefd[0];
	return (ST_OK);
}

static int	s_get_next_word(const size_t s_size, char *s, size_t *word_index, size_t *word_size)
{
	size_t	s_index;

	*word_index = 0;
	*word_size = 0;
	s_index = 0;
	while (s_index < s_size &&
		   (ft_isspace(s[s_index]) || s[s_index] == '<' || s[s_index] == '>'))
	{
		s_index++;
	}
	*word_index = s_index;
	while (s_index < s_size &&
		   !(ft_isspace(s[s_index]) || s[s_index] == '<' || s[s_index] == '>'))
	{
		s_index++;
	}
	*word_size = s_index - *word_index;
	return (*word_size ? 1 : 0);
}

typedef struct	s_parser
{
	t_buffer	token;
	int			(*func)(t_proc *, const char *);
}				t_parser;

#define TOKEN_ID__UNDEFINED		(size_t)-1
const t_parser parser[] = {
	{ STRING_TO_BUFFER(">>"), &redirection_dbl_chevr_right },
	{ STRING_TO_BUFFER(">"), &redirection_chevr_right },
	{ STRING_TO_BUFFER("<<"), &redirection_dbl_chevr_left },
	{ STRING_TO_BUFFER("<"), &redirection_chevr_left }
};

static int	s_get_next_token(char *s, size_t *token_id, size_t *token_index, size_t *token_size)
{
	size_t	s_size;
	size_t	s_index;
	size_t	parser_index;

	*token_id = TOKEN_ID__UNDEFINED;
	s_size = ft_strlen(s) + 1;
	s_index = 0;
	while (s_index < s_size)
	{
		parser_index = 0;
		while (parser_index < sizeof(parser) / sizeof(parser[0]))
		{
			if (s_index + parser[parser_index].token.size < s_size &&
				!ft_memcmp(s + s_index,
						   parser[parser_index].token.bytes,
						   parser[parser_index].token.size))
			{
				*token_id = parser_index;
				if (!s_get_next_word(s_size - s_index, s + s_index, token_index, token_size))
					return (0);
				*token_index += s_index;
				return (1);
			}
			parser_index++;
		}
		s_index++;
	}
	return (0);
}

static int	s_parse_redirection(t_proc *proc, char *s)
{
	size_t	s_index;
	size_t	token_id;
	size_t	token_index;
	size_t	token_size;
	char	*token;

	s_index = 0;
	while (s_get_next_token(s + s_index, &token_id, &token_index, &token_size))
	{
		token = ft_strsub(s, s_index + token_index, token_size);
		if (token == NULL)
		{
			display_status(ST_MALLOC, "parser", "ft_strsub");
			return (0);
		}
		log_debug("token %s", token);

		int ret;
		ret = parser[token_id].func(proc, token);
		if (ret != ST_OK)
		{
			display_status(ret, "parser", parser[token_id].token.bytes);
			free(token);
			return (ret);
		}
		free(token);
		s_index += token_index + token_size;
	}
	if (token_id != TOKEN_ID__UNDEFINED)
	{
		display_status(ST_UNEXPECTED_TOKEN, "parser", parser[token_id].token.bytes);
		return (0);
	}
	return (1);
}

static int	s_get_cmd(char *s, char **cmd, char **left)
{
	size_t	i;

	*cmd = s;
	*left = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			ft_memmove(&s[i + 1], &s[i], ft_strlen(&s[i]) + 1);
			*left = &s[i + 1];
			s[i] = '\0';
			break ;
		}
		i++;
	}
	return (1);
}

/*
** For now input shall be well espaced
** For now parse support only one command without special operator
** ex : COMMAND [OPTIONS] : ls -l ../my_dir/
** WARNING: ft_strsplit return array even if input length == 0
*/

t_job *s_job_create(char **array, char const *input, char **envp)
{
	int		i;
	t_job	*j;
	t_list	*p_node;
	char	**p_array;

	if ((j = job_alloc(input)) == NULL)
		return (NULL);
	list_push_back(&j->list_job, &g_current_jobs_list_head);
	i = 0;
	while (array[i] != NULL)
	{
		char *cmd, *left;

		s_get_cmd(array[i], &cmd, &left);
		log_debug("cmd {%s} left {%s}", cmd, left);

		p_array = ft_strsplit(cmd, ' ');
		if ((p_node = list_node__proc_alloc(j, cmd, p_array, envp)) == NULL)
			return (NULL);
		if (left)
		{
			if (!s_parse_redirection(CONTAINER_OF(p_node, t_proc, list_proc), left))
				return (NULL);
		}
		list_push_back(p_node, &j->proc_head);
		i++;
	}

	// temporary to test background jobs
	char **tmp = ft_strsplit(input, ' ');
	i = 0;
	while (tmp[i])
	{
		if (ft_strcmp(tmp[i], "&") == 0)
			j->foreground = 0;
		i++;
	}
	ft_memdel_tab((void ***)&tmp);
	return (j);
}

int	parse(t_sh *sh, char const *input)
{
	int		exit_status;
	t_job	*j;
	char	*cleaned;
	char	**array;
	t_lexer l;

	job_list_clean(1);
	j = NULL;
	cleaned = ft_strser(input);
	lexer(cleaned, &l);
	if (ft_strlen(cleaned) > 0 && (array = ft_strsplit(cleaned, '|')) != NULL)
	{
		if ((j = s_job_create(array, input, sh->envp)) == NULL)
		{
			log_fatal("parse job");
			return (-1);
		}
		ft_memdel_tab((void ***)&array);
		exit_status = job_launch(sh, j);
		if (exit_status != ST_OK)
		{
			log_fatal("job launch error: %s", i18n_translate(exit_status));
			return (exit_status);
		}
	}
	ft_strdel(&cleaned);
	return (ST_OK);
}
