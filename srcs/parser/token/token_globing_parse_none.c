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
			str[i] = str[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

static int	s_suite(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (TOKEN_CODE(*i) == TC_LASTEXITSTATUS)
	{
		log_fatal("there is a last exit stat yeah");
		if ((tmp = ft_itoa(parser->sh->last_exit_status)) == NULL)
			return (ST_MALLOC);
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
														tmp);
		free(tmp);
	}
	else if (TOKEN_CODE(*i) == TC_DOLLAR ||
		((*i + 1) < lexer->size && TOKEN_CODE(*i + 1) == TC_DOLLAR))
	{
		log_warn("Lexer size %d valeur du token=%s", lexer->size, TOKEN_CONTENT(*i + 1));
		log_warn("input value=%s", parser->in);
		local_var_replace(&parser, lexer, i);
		log_success("Valule of *i = %d", *i);
		// if ((tmp = local_var_replace(&parser->in, parser->sh)) != NULL)
		// {
		// 	log_warn("Parser-in %s", parser->in); //put this inside var replace et incrementer
		// 	ret = token_globing_parse_utils_push_str(parser->target_list_head, tmp);
		// 	free(tmp);
		// 	if (*i < lexer->size)
		// 		*i += lexer->size - 1;
		// }
		// else
		// 	*i += 1;
	}
	else
	{
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
					s_expand_escape_char_not_inhibited(TOKEN_CONTENT(*i)));
	}
	return (ret);
}

int			token_globing_parse_none(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	t_argv	*argument;
	char	*tmp;
	char	*tmp2;
	int		ret;

	ret = ST_OK;
	argument = (t_argv *)target;
	if (*i == 0 && TOKEN_CODE(*i) == TC_TILDE)
	{
		tmp = env_get_home(parser->sh->envp);
		if (tmp)
		{
			tmp2 = argument->buffer;
			if ((argument->buffer = ft_strdup(tmp)) == NULL)
				return (ST_MALLOC);
			free(tmp2);
		}
	}
	else
		ret = s_suite(parser, lexer, i);
	(*i)++;
	log_success("EXIT New input %s", parser->in);
	return (ret);
}
