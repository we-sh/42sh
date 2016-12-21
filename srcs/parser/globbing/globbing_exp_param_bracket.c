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

static void s_globbing_bracket_exp_subsequence(t_tmp **concat, int i)
{
	unsigned char range_start;
	unsigned char range_end;
	char 					*tmp_value;
	char 					*new_value;
	int 					first;
		
	first = 0;
	char 					*concat_before;

	if (i > 0)
	{
		concat_before = ft_strnew(i);
		concat_before = ft_strncpy(concat_before, (*concat)->value, i);
		log_debug("There is a before: %s",concat_before);
	}
	else
		concat_before = NULL;

	range_start = (*concat)->value[i];
	range_end = (*concat)->value[i+2];
	log_debug("Display range limit: value[%d]=%c value[%d]=%c",i,range_start,i+2,range_end);
	

	int len;
	int j=0;
	len = range_end - range_start;
	if (len <= 0) // recherche [Z-A] pas prise en compte ?
		return ;
	new_value = (char*)malloc(sizeof(char) * len);
	while (range_start <= range_end)
	{
		log_debug("Display range start:%d=%c range_end: %d=%c",range_start,range_start,range_end,range_end);
		if (ft_isalnum((unsigned char)range_start) || first == 0)
		{
			new_value[j] = range_start;
			j++;
			first++;
		}
		range_start++;
	}
	tmp_value = ft_strdup((*concat)->value+3);
	free((*concat)->value);
	(*concat)->value = ft_strjoin3_safe(concat_before, new_value, tmp_value);
	free(new_value);
	free(tmp_value);
}

static int  globbing_bracket_recurse(t_mylist **list,t_tmp *concat, char *match, int i)
{
	char c[2];
	char *sub_list;

	c[0] = concat->value[i];
	c[1] = '\0';
	sub_list = ft_strjoin3_safe(concat->before, c, concat->after);
	log_success("Sub_list: %s", sub_list);
//	log_success("Compare if Char match:%c, string:%s, char:%c", sub_list[i], match, match[i]);

	 int j=0;
	// while (sub_list[cmp])
	// {
		log_success("Compare int cmp:%d, Char match:%c, char:%c", i, c[0], match[j]);
		log_success("Compare concat->value[%d]:%s,", i, c);
		if (c[0] != '*' && c[0] != match[j])
		{
			free(sub_list);//ADD A LA DERNIERE MINUTE PEU CRASH
			return 1;
		}
		// cmp++;
	// }
	globbing_bracket(list, sub_list, match);
	log_error("Globbing new sub_list: %s", sub_list);
	free(sub_list);//ADD A LA DERNIERE MINUTE PEU CRASH
	return 0;
}

void	globbing_exp_param_bracket(t_mylist **list, char *input, char *after_open_brack, char *after_closing_brack, char *match)
{
	t_tmp 				*concat;
	int 					i=0;
	int 		ret=0;


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
					(ft_isalnum(concat->value[i+2])))
			s_globbing_bracket_exp_subsequence(&concat, i);
	 	if(ft_strchr(input, '[') != NULL)
	 	{
	 		if ((ret = globbing_bracket_recurse(list, concat, match, i)) == 1)
	 		{
	 			i++;
	 			continue ;
	 		}
			i++;
	 	}
		log_debug("before add_new_arg:%s , %c", concat->value, concat->value[i]);

		s_add_new_arg(list, concat, concat->value[i]);
		i++;
		return ;	 		
	}
	free(concat->value);
	free(concat->before);
	free(concat->after);
	free(concat);
}