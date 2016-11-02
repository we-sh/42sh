#include "shell.h"

static int		s_local_var_replace_checkfirst_value(t_parser *parser, int *i, char **input)
{
	if (P_TOKEN_CODE(*i + 1) != TC_DOLLAR)
	{
		if ((*input = ft_strdup(P_TOKEN_CONTENT(*i + 1))) == NULL)
		 return (ST_MALLOC);
	}
	return (ST_OK);
}

static int		s_local_var_replace_loop(t_parser *parser, char *input)
{
	t_var		*ptr;
	int			ret;

	ptr = parser->sh->local_vars;
	while (ptr)
	{
		if (ft_strcmp(input, ptr->key) == 0)
		{
			if ((ret = token_globing_parse_utils_push_str(parser->target_list_head,
				ptr->value)) != ST_OK)
				return (ret);
			break ;
		}
		ptr = ptr->next;
	}
	return (ST_OK);
}

int				local_var_replace(t_parser *parser, int *i)
{
	int			ret;
	char		*input;

	ret = ST_OK;
	if (P_TOKEN_CODE(*i + 1) == TC_DOLLAR || P_TOKEN_CONTENT(*i + 1)[0] == '?')
	{
		if (P_TOKEN_CODE(*i + 1) == TC_DOLLAR)
			ret = parser->sh->pgid;
		else
			ret = parser->sh->last_exit_status;
		if((input = ft_itoa(ret)) == NULL)
			return (ST_MALLOC);
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
														input);
	}
	else if ((ret = s_local_var_replace_checkfirst_value(parser, i, &input)) != ST_OK)
		return (ret);
	if (parser->sh->local_vars && (ret = s_local_var_replace_loop(parser, input)) != ST_OK)
		return (ret);
	free(input);
	return (ret);
}