#include "parser.h"

/*
** These functions are able to apply an action on a specific token received.
** For example, the semi-column token, when it is detected, will return 1,
** which means for the parser that the job is finished.
** WARNING : the parameters should be unconsistent, or some are missing...
** WQRNING : this is one file per token...
*/



// ----------------------------------------------------------------
// todo: to be exported to libft submodule
static int			ft_array_push_back(char ***array, char const *value)
{
	char	**new_array;
	size_t	total;

	if (!value || !array)
		return (-1);
	total = 0;
	if (*array)
		while ((*array)[total])
			total++;
	if ((new_array = (char **)malloc(sizeof(char *) * (total + 2))) == NULL)
		return (-1);
	total = 0;
	if (*array)
		while ((*array)[total])
		{
			if ((new_array[total] = ft_strdup((*array)[total])) == NULL)
				return (-1);
			total++;
		}
	if ((new_array[total] = ft_strdup(value)) == NULL)
		return (-1);
	new_array[total + 1] = NULL;
	ft_memdel_tab((void ***)&(*array));
	*array = new_array;
	return (total);
}
// ----------------------------------------------------------------




int	token_parse_none(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s", "TT_NONE");
	log_trace("token type %d token code %d", lexer->tokens[*i].type, lexer->tokens[*i].code);

	char	*tmp;

	if (lexer->tokens[*i].type == TT_NAME && lexer->tokens[*i].code == TC_NONE)
	{
		tmp = expand(p, &lexer->tokens[*i], *i > 0 ? &lexer->tokens[*i - 1] : NULL);
		if (ft_array_push_back(&p->argv, tmp) < 0)
		{
			log_fatal("failed to push `%s` intro p->argv", lexer->tokens[*i].content);
		}
		ft_memdel((void **)&tmp);
	}

	// replace with array push in argv
	if (!(p->command))
		p->command = ft_strdup(lexer->tokens[*i].content );
	else
	{
		tmp = ft_strjoin(p->command, lexer->tokens[*i].content);
		free(p->command);
		p->command = tmp;
	}
	return (0);
}