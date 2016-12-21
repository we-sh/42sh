#include "shell.h"

static char *s_check_last_bracket(char *input)
{
	char *endofbracket;

	endofbracket = input;
	if ((endofbracket = ft_strchr(endofbracket, ']')) == NULL)
		return (NULL);
	log_info("Start with bracket %s et end with:%s", input, endofbracket);		
	return (endofbracket);
}


void globbing_bracket(t_mylist **list, char *input)
{
	char 				*after_first_brack;
	char 				*endofinput;

	log_debug("AA Globbing_bracket list expansion on `%s'", input);
	if ((after_first_brack = ft_strchr(input, '[')) != NULL)
	{
		if ((endofinput = (s_check_last_bracket(input))) == NULL)
		{
				log_error("Ending bracket Missing%s", input);
				globbing_happend_to_list(list, input);
		}
		else
		{
				log_success("Ending bracket Succes");
				log_success("Full input :%s", input);
				log_success("str after first [ :%s", after_first_brack);
				log_success("str after ] :%s", endofinput);
				globbing_exp_param_bracket(list, input, after_first_brack, endofinput);
		}
	}
	else
	{
		log_success("No bracket inside input");
		globbing_happend_to_list(list, input);
	}
}
