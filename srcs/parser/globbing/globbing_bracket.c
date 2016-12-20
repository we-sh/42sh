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

static void s_happend_to_list(t_mylist **list, char *input)
{
	t_mylist		*newm;
	t_mylist		*ptr;

	if (*list == NULL)
	{
		log_info("FIRST: %s", input);
		*list = (t_mylist*)ft_memalloc(sizeof(t_mylist));
		(*list)->content = ft_strdup(input);
		(*list)->next = NULL;
	}
	else
	{
		log_info("Second: %s", input);
		newm = (t_mylist*)ft_memalloc(sizeof(t_mylist));
		ptr = *list;
		while (ptr->next)
		{
			log_info("Value of ptr->content `%s'", ptr->content);
			ptr = ptr->next;
		}
		ptr->next = newm;
		newm->content = ft_strdup(input);
		newm->next = NULL;
	}
}

static void s_add_new_arg(t_mylist **list, char *before, char *after, char value_i)
{
	t_mylist *ptr;
	char *full;
	char c[2];

	ptr = *list;
	// log_success("before :%s", before);
	// log_success("Value[%d] :%c",i, value[i]);
	// log_success("after :%s", after);
	c[0] = value_i;
	c[1] = '\0';
	log_success("valeur de c :%s", c);
	full = ft_strjoin3_safe(before, c, after);
	log_success("full :%s", full);
	while (ptr)
	{
		if (ft_strcmp(ptr->content, full) == 0)
		{
			log_success("Match ptr->content", ptr->content);
			free(full);	
			return ;
		}
		ptr = ptr->next;
	}
	s_happend_to_list(list, full);
	log_success("Happen: list:%s, full:%s ", (*list)->content, full);
	free(full);
}

static void s_expand_bracket_params(t_mylist **list, char *input, char *after_first_brack, char *endofinput)
{
	char *value;
	char *before;
	char *after;
	int len;
	int i=0;

	len = ft_strlen(after_first_brack+1) - ft_strlen(endofinput);
	value = ft_strsub((after_first_brack+1), 0, len);
	len = ft_strlen(input) - ft_strlen(after_first_brack);
	before = ft_strsub(input, 0, len);
	len = ft_strlen(input) - ft_strlen(after_first_brack);
	after = ft_strdup(endofinput+1);
			log_debug("value:%s",value);
			log_debug("before:%s",before);
			log_debug("after:%s",after);
	while (value[i] != '\0')
	{

		//subsequence
		unsigned int range_start;
		unsigned int range_end;
		int first;
		
		first = 0;
		if (value[i+1] == '-' && 
			(value[i+2] != ']' && value[i+2] != '-' && value[i+2] != '\0'))
		{
			range_start = value[i];
			range_end = value[i+2];
			log_debug("Display range limit: value[%d]=%c value[%d]=%c",i,range_start,i+2,range_end);
			
			while (range_start <= range_end)
			{
				log_debug("Display range start:%d=%c range_end: %d=%c",range_start,range_start,range_end,range_end);
				if (ft_isalnum((unsigned char)range_start) || first == 0)
				{
					s_add_new_arg(list, before, after, (unsigned char)range_start);
					first++;
				}
				range_start++;
			}
			i +=3;
		}
		else
			s_add_new_arg(list, before, after, value[i]);
		i++;
	}
//				log_success("Value :%s", value);
	free(value);
	free(before);
	free(after);
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
				s_happend_to_list(list, input);
		}
		else
		{
				log_success("Ending bracket Succes");
				log_success("Full input :%s", input);
				log_success("str after first [ :%s", after_first_brack);
				log_success("str after ] :%s", endofinput);
				s_expand_bracket_params(list, input, after_first_brack, endofinput);
		}
	}
	else
	{
		log_success("No bracket inside input");
		s_happend_to_list(list, input);
	}
}
