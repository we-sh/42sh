#include "shell.h"

static char	*s_expand_escape_char_not_inhibited(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '\\' && str[j + 1] == '\n')
			j += 2;
		else
		{
			if (str[j] == '\\' && str[j + 1] != '\\')
				j++;
			else if (str[j] == '\\' && str[j - 1] != '\\')
				j++;
			str[i] = str[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

static int	s_suite(t_parser *parser, char *output)
{
	int		ret;

	ret = token_globing_parse_utils_push_str(parser->target_list_head,
					s_expand_escape_char_not_inhibited(output));
	return (ret);
}

static int	s_replace_tilde(t_parser *parser, void *target, char *output)
{
	t_argv	*argument;
	char	*tmp;
	char	*tmp2;

	argument = (t_argv *)target;
	tmp = env_get_home(parser->sh->envp);
	if (tmp)
	{
		tmp2 = argument->buffer;
		if ((argument->buffer = ft_strjoin(tmp, output + 1)) == NULL)
			return (ST_MALLOC);
		free(tmp2);
	}
	return (ST_OK);
}

int			token_globing_parse_none(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;
	char	*output;

	ret = ST_OK;
	output = NULL;
	if ((ret = local_var_replace(parser->sh, TOKEN_CONTENT(*i), &output))
		!= ST_OK)
		return (ret);
	if (ft_strlen(output) > 0)
	{
		((t_argv *)target)->is_null = 0;
		if (*i == 0 &&
			(output[0] == '~' && (output[1] == '\0' || output[1] == '/')))
		{
			if ((s_replace_tilde(parser, target, output)) == ST_MALLOC)
				return (ST_MALLOC);
		}
		else
			ret = s_suite(parser, output);
	}
	(*i)++;
	free(output);
	return (ret);
}
