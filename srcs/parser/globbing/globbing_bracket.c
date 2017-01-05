#include "shell.h"

char		*globbing_check_last_bracket(char *input)
{
	int		last_bracket;
	char	*endofbracket;
	int		i;

	i = 0;
	last_bracket = 0;
	while (input[i])
	{
		if (input[i - 1] != '!' && input[i] == ']' && i > 1)
		{
			last_bracket = i;
			break ;
		}
		else if (input[i - 1] == '!' && input[i] == ']' && i > 2)
		{
			last_bracket = i;
			break ;
		}
		i++;
	}
	endofbracket = input + last_bracket;
	if (last_bracket == 0)
		return NULL;
	return (endofbracket);
}

static void	s_free_concat(t_tmp *concat)
{
	free(concat->value);
	free(concat->before);
	free(concat->after);
	free(concat);
}

static int s_concat_arg(t_tmp **concat, char *after_open_brack, char *after_closing_brack, char *input)
{

	if ((*concat = (t_tmp*)ft_memalloc(sizeof(t_tmp))) == NULL)
		return (ST_MALLOC);
	if (((*concat)->value = ft_strsub(after_open_brack + 1, 0,
		(ft_strlen(after_open_brack + 1) - ft_strlen(after_closing_brack)))) == NULL)
		return (ST_MALLOC);
	if (((*concat)->before = ft_strsub(input, 0, (ft_strlen(input) - ft_strlen(after_open_brack)))) == NULL)
		return (ST_MALLOC);
	if (((*concat)->after = ft_strdup(after_closing_brack + 1)) == NULL)
		return (ST_MALLOC);
	(*concat)->reverse = 0;
	return (ST_OK);
}

static int s_expand(t_mylist **list, char *input, t_tmp *concat, char *match)
{
	if ((globbing_exp_param_bracket(list, input, concat, match)) == -1)
	{
		s_free_concat(concat);
		return (-1);
	}
	s_free_concat(concat);
	return (ST_OK);
}

int			globbing_bracket(t_mylist **list, char *input, char *match)
{
	char	*after_open_brack;
	char	*after_closing_brack;
	t_tmp	*concat;

	if ((after_open_brack = ft_strchr(input, '[')) != NULL)
	{
		if ((after_closing_brack = (globbing_check_last_bracket(input))) == NULL)
		{
			if ((globbing_happend_to_list(list, input)) == ST_MALLOC)
				return (ST_MALLOC);
		}
		else
		{
			if ((s_concat_arg(&concat, after_open_brack, after_closing_brack, input)) == ST_MALLOC)
				return (ST_MALLOC);
			return (s_expand(list, input, concat, match));
		}
	}
	else
	{
		if ((globbing_happend_to_list(list, input)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}
