#include "shell.h"

static int		s_local_var_replace_checkfirst_value_insert(t_parser **parser, int *i, int pos)
{
	char		*firstvalue;
	int			ret;

	ret = 0;
	if ((firstvalue = (char *)malloc(sizeof(char)* pos + 1)) == NULL)
		return (ST_MALLOC);
	firstvalue = ft_strncpy(firstvalue, (*parser)->in, pos);
	firstvalue[pos] = '\0';
	if ((ret = token_globing_parse_utils_push_str((*parser)->target_list_head,
		firstvalue)) != ST_OK)
	{
		free(firstvalue);
		return (ret);
	}
	*i += 1;
	free(firstvalue);
	return (ST_OK);
}

static int		s_local_var_replace_checkfirst_value(t_parser **parser, int *i, char **input)
{
	int			pos;

	pos = 0;
	if (ft_strncmp((*parser)->in, "$", 1) != 0)
	{
		while (ft_strncmp((*parser)->in + pos, "$", 1) != 0)
			pos++;
		if ((s_local_var_replace_checkfirst_value_insert(parser, i, pos)) == ST_MALLOC)
			return (ST_MALLOC);
		if ((*input = ft_strdup((*parser)->in + pos)) == NULL)
		 return (ST_MALLOC);
	}
	else
	{
		if ((*input = ft_strdup((*parser)->in)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

static int		s_local_var_replace_loop(t_parser **parser, int *i, char *tab)
{
	t_var		*ptr;
	int			ret;

	ptr = (*parser)->sh->local_vars;
	while (ptr)
	{
		if (ft_strcmp(tab, ptr->key) == 0)
		{
			if ((ret = token_globing_parse_utils_push_str((*parser)->target_list_head,
				ptr->value)) != ST_OK)
			{
				ft_memdel_tab((void ***)&tab);
				return (ret);
			}
			else
				break ;
		}
		ptr = ptr->next;
	}
	*i += 2;
	return (ST_OK);
}

static int		s_local_var_replace_split(t_parser **parser, int *i, char *input)
{
	char		**tab;
	int			z;

	z = 0;
	if ((tab = ft_strsplit(input, '$')) == NULL)
		return (ST_MALLOC);
	while (tab[z])
	{
		s_local_var_replace_loop(parser, i, tab[z]);
		z++;
	}
	ft_memdel_tab((void ***)&tab);
	return (ST_OK);
}

int				local_var_replace(t_parser **parser, t_lexer *lexer, int *i)
{
	int			ret;
	char		*input;

	input = NULL;
	ret = ST_OK;
	if ((ret = s_local_var_replace_checkfirst_value(parser, i, &input)) != ST_OK)
		return (ret);
	if (!(*parser)->sh->local_vars)
		*i += lexer->size - 1;
	else
	{
		if ((ret = s_local_var_replace_split(parser, i, input)) != ST_OK)
			return (ret);
	}
	free(input);
	return (ST_OK);
}