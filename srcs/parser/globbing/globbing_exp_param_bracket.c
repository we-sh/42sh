#include "shell.h"

static void s_add_new_arg(t_mylist **list, char value_i)
{
	t_mylist *ptr;
	char *full;
	char c[2];

	// log_success("before :%s", before);
	// log_success("Value[%d] :%c",i, value[i]);
	// log_success("after :%s", after);
	ptr = *list;
	c[0] = value_i;
	c[1] = '\0';
	log_success("valeur de c :%s", c);
	full = ft_strjoin3_safe((*list)->before, c, (*list)->after);
	log_success("full :%s", full);
	while (ptr)
	{
		if (ptr->content && ft_strcmp(ptr->content, full) == 0)
		{
			log_success("Match ptr->content", ptr->content);
			free(full);	
			return ;
		}
		ptr = ptr->next;
	}
	globbing_happend_to_list(list, full);
	log_success("Happen: list:%s, full:%s ", (*list)->content, full);
	free(full);
}

static void s_globbing_bracket_subsequence(t_mylist **list, int i)
{
	unsigned int range_start;
	unsigned int range_end;
	int first;
		
	first = 0;
	range_start = (*list)->value[i];
	range_end = (*list)->value[i+2];
	log_debug("Display range limit: value[%d]=%c value[%d]=%c",i,range_start,i+2,range_end);
	
	while (range_start <= range_end)
	{
		log_debug("Display range start:%d=%c range_end: %d=%c",range_start,range_start,range_end,range_end);
		if (ft_isalnum((unsigned char)range_start) || first == 0)
		{
			s_add_new_arg(list, (unsigned char)range_start);
			first++;
		}
		range_start++;
	}
}

void  globbing_exp_param_bracket(t_mylist **list, char *input, char *after_first_brack, char *endofinput)
{
	int i=0;

//	len = ft_strlen(after_first_brack+1) - ft_strlen(endofinput);
  *list = (t_mylist*)ft_memalloc(sizeof(t_mylist));
	(*list)->content = NULL;
	(*list)->next = NULL;
	(*list)->value = ft_strsub(after_first_brack+1, 0, (ft_strlen(after_first_brack+1) - ft_strlen(endofinput)));
//	len = ft_strlen(input) - ft_strlen(after_first_brack);
	(*list)->before = ft_strsub(input, 0, (ft_strlen(input) - ft_strlen(after_first_brack)));
	(*list)->after = ft_strdup(endofinput+1);
			log_debug("value:%s",(*list)->value);
			log_debug("before:%s", (*list)->before);
			log_debug("after:%s",(*list)->after);
	while ((*list)->value[i] != '\0')
	{
		if ((*list)->value[i+1] == '-' && 
					((*list)->value[i+2] != ']' &&
						(*list)->value[i+2] != '-' &&
						(*list)->value[i+2] != '\0'))
		{
			s_globbing_bracket_subsequence(list, i);
			i +=3;
		}
		else
		{
			s_add_new_arg(list, (*list)->value[i]);
			i++;
		}
	}
//        log_success("Value :%s", value);
	free((*list)->value);
	free((*list)->before);
	free((*list)->after);
}