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

static 		int s_istilde(char *input)
{
	if (input[0] == '~' && (input[1] == '\0' || input[1] == '/'))
		return (1);
	return (0);
}

int			token_globing_parse_none(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	t_argv	*argument;
	char	*tmp;
	char	*tmp2;
	int		ret;
	char	*output;

	ret = ST_OK;
	argument = (t_argv *)target;
	log_warn("Token GLOBING PARSE-NONE debug lexer number %d", lexer->size);
	ret = 0;
	output = NULL;
	if((ret = local_var_replace(parser->sh, TOKEN_CONTENT(*i), &output)) != ST_OK)
		return (ret);
	if (*i == 0 && s_istilde(output))
	{
		tmp = env_get_home(parser->sh->envp);
		if (tmp)
		{
			tmp2 = argument->buffer;
			if ((argument->buffer = ft_strjoin(tmp, output + 1)) == NULL)
				return (ST_MALLOC);
			free(tmp2);
		}
	}
	else
		ret = s_suite(parser, output);
	(*i)++;
	free(output);
	log_success("EXIT New input %s", parser->in);
	return (ret);
}
