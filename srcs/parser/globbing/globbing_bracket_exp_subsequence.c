#include <shell.h>

static char *s_globbing_increment_range(char *concat_value, unsigned char range_start, unsigned char range_end, int len)
{
	char *new_value;
	// char *tmp_value;
	int						j;
	char					tmp_start;

	(void)concat_value;
	j = 0;
	tmp_start = range_start;
	if ((new_value = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	log_info("len of subsequence: %d",len);
	
	while (tmp_start <= range_end)
	{
		if (tmp_start)
		{
			log_debug("Display range start:%d=%c range_end: %d=%c", tmp_start, tmp_start, range_end, range_end);
				new_value[j] = tmp_start;
			j++;
		}
		tmp_start++;
	}
	new_value[j] = '\0';
	return (new_value);
}

static int			s_globbing_expand_range(t_tmp **concat, char *concat_before, int i)
{
	unsigned char	range_start;
	unsigned char	range_end;
	int						len;
	char 					*new_value;
	char 					*tmp_value;


	//check tous les ranges a venir et les expandes

	log_info("concat_before:%s", concat_before);
	log_info("Value de i:%d", i);
	// log_info("concat_after:%s", concat_after);
	range_start = (*concat)->value[i];
	range_end = (*concat)->value[i + 2];
	log_debug("Display range limit: value[%d]=%c value[%d]=%c",i,range_start,i+2,range_end);

	len = range_end - range_start; // verife de l'ordre
	if (len <= 0) // recherche [Z-A] pas prise en compte ?
		return 0;
	else
		new_value = s_globbing_increment_range((*concat)->value, range_start, range_end, len);

//  tmp_value = ft_strdup((*concat)->value+3);
	log_info("concat_before=%s, value of new-value: %s",concat_before, new_value);


 	if (i > 0) //chope le before
	{
		tmp_value = ft_strnew(i);
		tmp_value = ft_strncpy(tmp_value, (*concat)->value, i);
		(*concat)->value = ft_strjoin(tmp_value, new_value);
		log_info("Apres Expend 1 concat->value: %s",(*concat)->value);
		free(tmp_value);
	}
	else
	{
		(*concat)->value = ft_strdup(new_value);
		log_info("Apres Expend 2 concat->value: %s",(*concat)->value);	
	}
	free(new_value);
	return (len);
}

static void s_remove_double(t_tmp **concat)
{
	char	char_tab[127];
	int 	i;
	int 	j;
	int 	len;
	char 	*new_value;

	i = 0;
	j = 0;
	len = 0;
	ft_bzero(char_tab, 127);

	while ((*concat)->value[i])
	{
		char_tab[(int)(*concat)->value[i]] = 1;
	log_warn("putin de lenchar_tab[(int)(*concat)->value[%d]]: %d", i, char_tab[(int)(*concat)->value[i]]);
		i++;
	}


	i = 0;

	while (i < 127)
	{
		if (char_tab[i] == 1)
			len++;
		i++;
	}

	ft_bzero(char_tab, 127);
	log_warn("putin de len: %d", len);
	if ((new_value = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return ;

	i = 0;

	while((*concat)->value[i])
	{
		if (char_tab[(int)(*concat)->value[i]] == 0)
		{

			new_value[j] = (*concat)->value[i];

			char_tab[(int)(*concat)->value[i]] = 1;
			
			j++;
		}

		i++;
	}

	free((*concat)->value);
	(*concat)->value = ft_strdup(new_value);
}

static void s_reverse_it(t_tmp **concat) // Mettre un return sur la fonction pour check memory alloc
{
	char ptr;
	char *tmp_value;
	int j;
	int len;

	j = 0;
	ptr = 32;	
	len = ft_strlen((*concat)->value);
	len = 127 - 32 - len;

	if ((tmp_value = (char *)malloc(sizeof(char) * len) + 1) == NULL)
		return ;
	while (ptr < 127)
	{
		if (!ft_strchr((*concat)->value, ptr) || ptr == '!')
		{
			tmp_value[j] = ptr;
			j++;
		}
		ptr++;
	}
	tmp_value[j] = '\0';
	free((*concat)->value);
	(*concat)->value = tmp_value;
	log_success("!Globbing_increment_range new_value:%s", (*concat)->value);
}

void					globbing_bracket_exp_subsequence(t_tmp **concat, int i)
{
	char				*tmp_value_after_range;
	char				*tmp_concat_value;
	int					len;
	int					ret;

	len = ft_strlen((*concat)->value);
	log_info("Value of concat inside subsequence: %s",(*concat)->value);
	log_info("Value of i: %d",i);
	log_info("Value of len: %d",len);

	while ((*concat)->value[i] != '\0')
	{
		if (i + 2 < len)
		{
			if ((*concat)->value[i+1] == '-' && 
						((*concat)->value[i+2])) // il y a une range
			{
				log_info("Is range:%s", ((*concat)->value+i));
				log_info("Value of len: %d",len);
				log_info("Value of i: %d",i);
				tmp_value_after_range = ft_strdup((*concat)->value + i + 3); // verifier ca
				log_info("tmp_value_after_range: %s",tmp_value_after_range);


				if ((ret = s_globbing_expand_range(concat, (*concat)->before, i)) != 0)
				{
					log_info("EXP SUB value of ret:%d", ret);
					log_info("Expend range (*concat)->value:%s", (*concat)->value);
					tmp_concat_value = ft_strdup((*concat)->value);//check le return
					free((*concat)->value);
					(*concat)->value = ft_strjoin(tmp_concat_value , tmp_value_after_range); //check le return, check value inside each param
					free(tmp_concat_value);
					log_info("Expend range (*concat)->value + after:%s", (*concat)->value);
					len = ft_strlen((*concat)->value);
					i += ret;
				}
				free(tmp_value_after_range);
			}
		}
		if ((*concat)->value[i])// && ft_isalnum((*concat)->value[i])) //Doit on check is allnum ?
		{
			log_info("Normal i=%d, char  = %c", i, (*concat)->value[i]);
			i++;
		}
	}
	log_info(" OLD!! Concat->value:%s", (*concat)->value);
	s_remove_double(concat);
	log_info(" OLD!! Concat->value:%s", (*concat)->value);
	if ((*concat)->reverse == 1)
		s_reverse_it(concat);
}
