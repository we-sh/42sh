#include "shell.h"

char		*globbing_check_last_bracket(char *input)
{
  int   last_bracket;
	char	*endofbracket;
	int		i;

	i = 0;
	last_bracket = 0;
	while (input[i])
	{
		if (input[i-1] != '!' && input[i] == ']' && i > 1)
		{
			last_bracket = i;
			break ;
		}
		else if (input[i-1] == '!' && input[i] == ']' && i > 2)
		{
			last_bracket = i;
			break ;
		}
		i++;
	}
	endofbracket = input + last_bracket;
	log_info("Start with bracket %s et end with:%s", input, endofbracket);
	if (last_bracket == 0)
		return NULL;
	return (endofbracket);
}


int globbing_bracket(t_mylist **list, char *input, char *match)
{
	char 				*after_open_brack;
	char 				*after_closing_brack;

	log_debug("AA Globbing_bracket list expansion on `%s'", input);
	if ((after_open_brack = ft_strchr(input, '[')) != NULL)
	{
		if ((after_closing_brack = (globbing_check_last_bracket(input))) == NULL)
		{
			log_error("Ending bracket Missing: %s, after_closing:%s", input,after_closing_brack);
			globbing_happend_to_list(list, input);
		}
		else
		{
			log_success("Ending bracket Succes");
			log_success("Full input :%s", input);
			log_success("str after first [ :%s", after_open_brack);
			log_success("str after ] :%s", after_closing_brack);
			if ((globbing_exp_param_bracket(list, input, after_open_brack, after_closing_brack, match)) == -1)
				return (-1);
		}
	}
	else
	{
		log_success("No open bracket inside input return mal formed string");
		globbing_happend_to_list(list, input);
	}
	return (ST_OK);
}
