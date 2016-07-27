#include "shell.h"


static int s_local_var_replace_checkfirst_value(t_parser **parser, int *i, char **input)
{// checker le retour des malloc
	int pos;
	int ret;
	char *firstvalue;

	pos = 0;
	ret = 0;
	if (ft_strncmp((*parser)->in, "$", 1) != 0)
	{
		while (ft_strncmp((*parser)->in + pos, "$", 1) != 0)
			pos++;
		firstvalue = (char *)malloc(sizeof(char)* pos + 1);
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
		*input = ft_strdup((*parser)->in + pos); 
	}
	else
		*input = ft_strdup((*parser)->in);
	return (ST_OK);
}

static int		s_local_var_replace_loop(t_parser **parser, int *i)
{
	char *input;

	input = NULL;
	s_local_var_replace_checkfirst_value(parser, i, &input);

//	log_info("Value of input=%s", input);

	t_var *ptr;
	char **tab;
	int	z;
	int	ret;
	int	nbrptr;
	int	nbrvar;

	nbrptr = 0;
	nbrvar = 0;
	ptr = (*parser)->sh->local_vars;
	while (ptr)
	{
		nbrvar++;
		ptr = ptr->next;
	}
	z = 0;
	tab = ft_strsplit(input, '$');
	log_warn("INPUT before replace %s et *i=%d", input, *i);
	free(input);
	while (tab[z])
	{
		log_info("TAB[%d]->%s", z, tab[z]);
		ptr = (*parser)->sh->local_vars;
		nbrptr = 0;
		while (ptr)
		{
			log_success("BROWSE PTR");
			if (ft_strcmp(tab[z], ptr->key) == 0)
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
			nbrptr++;
			ptr = ptr->next;
		}
		*i += 2;
		log_success("TAB[%d]->%s", z, tab[z]);
		z++;
	}
	ft_memdel_tab((void ***)&tab);
	return (ST_OK);
}

int 		local_var_replace(t_parser **parser, t_lexer *lexer, int *i)
{
	int		ret;
	char	*input;

	input = NULL;
	ret = ST_OK;
	if (!(*parser)->sh->local_vars)
	{
		if ((ret = s_local_var_replace_checkfirst_value(parser, i, &input)) != ST_OK)
			return (ret);
		*i += lexer->size - 1;
		return (ST_OK);
	}
	else if ((ret = s_local_var_replace_loop(parser, i)) != ST_OK)
		return (ret);
	return (ST_OK);
}