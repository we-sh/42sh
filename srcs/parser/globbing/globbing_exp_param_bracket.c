#include "shell.h"

static void s_add_new_arg(t_mylist **list, t_tmp *concat, char value_i)
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
	full = ft_strjoin3_safe(concat->before, c, concat->after);
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

static void s_globbing_bracket_subsequence(t_mylist **list, t_tmp *concat, int i)
{
	unsigned int range_start;
	unsigned int range_end;
	int first;
		
	first = 0;
	range_start = concat->value[i];
	range_end = concat->value[i+2];
	log_debug("Display range limit: value[%d]=%c value[%d]=%c",i,range_start,i+2,range_end);
	while (range_start <= range_end)
	{
		log_debug("Display range start:%d=%c range_end: %d=%c",range_start,range_start,range_end,range_end);
		if (ft_isalnum((unsigned char)range_start) || first == 0)
		{
			s_add_new_arg(list, concat, (unsigned char)range_start);
			first++;
		}
		range_start++;
	}
}

void	globbing_exp_param_bracket(t_mylist **list, char *input, char *after_open_brack, char *after_closing_brack)
{
	t_tmp 				*concat;
	int i=0;
	char *after_open_brack_sub;
	char *after_closing_brack_sub;

	char *sub_list;
	char c[2];

  concat = (t_tmp*)ft_memalloc(sizeof(t_tmp));
	concat->value = ft_strsub(after_open_brack+1, 0, (ft_strlen(after_open_brack+1) - ft_strlen(after_closing_brack)));
	concat->before = ft_strsub(input, 0, (ft_strlen(input) - ft_strlen(after_open_brack)));
	concat->after = ft_strdup(after_closing_brack+1);
	
	log_debug("before:%s", concat->before);
	log_debug("value:%s",concat->value);
	log_debug("after:%s",concat->after);

	while (concat->value[i] != '\0')
	{
		if (concat->value[i+1] == '-' && 
					(concat->value[i+2] != ']' &&
						concat->value[i+2] != '-' &&
						concat->value[i+2] != '\0'))
		{
			s_globbing_bracket_subsequence(list, concat, i);
			i +=3;
		}
		else
		{
			/* 
				Recurse if the after part contain a new bracket 
			*/
			if ((after_open_brack_sub = ft_strchr(concat->after, '[')) != NULL)
			{
				log_error("value of after_OPEN: %s", after_open_brack_sub);
				if ((after_closing_brack_sub = globbing_check_last_bracket(concat->after)) == NULL)//ERROR SECOND NOT END
				log_error("ERROR CHECK HOW TO HANDLE IT");
				else
				{
					log_error("value of after_CLOsiING: %s", after_closing_brack_sub);
					while (concat->value[i] != '\0')
					{
						if (concat->value[i+1] == '-' && 
									(concat->value[i+2] != ']' &&
										concat->value[i+2] != '-' &&
										concat->value[i+2] != '\0'))
						{
							s_globbing_bracket_subsequence(list, concat, i);
							i +=3;
						}
						else
						{
							c[0] = concat->value[i];
							c[1] = '\0';
							sub_list = ft_strjoin3_safe(concat->before, c, concat->after);
							globbing_exp_param_bracket(list, sub_list, after_open_brack_sub, after_closing_brack_sub);
							log_error("value of (*list)->value): %s", concat->value);
							i++;
						}
					}
					free(concat->value);
					free(concat->before);
					free(concat->after);
					return ;
				}
			}
			s_add_new_arg(list, concat, concat->value[i]);
			i++;
		}
	}
//        log_success("Value :%s", value);
	free(concat->value);
	free(concat->before);
	free(concat->after);
}