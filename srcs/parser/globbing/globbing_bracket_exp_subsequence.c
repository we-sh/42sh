#include <shell.h>

static char *s_globbing_increment_range(unsigned char	range_start, unsigned char	range_end, int len)
{
	char *new_value;
	int						j;

	j = 0;
	if ((new_value = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	log_info("len of subsequence: %d",len);
	
	while (range_start <= range_end)
	{
		if (ft_isalnum((unsigned char)range_start))
		{
			log_debug("Display range start:%d=%c range_end: %d=%c",range_start,range_start,range_end,range_end);
			new_value[j] = range_start;
			j++;
		}
		range_start++;
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
	range_end = (*concat)->value[i+2];
	log_debug("Display range limit: value[%d]=%c value[%d]=%c",i,range_start,i+2,range_end);

	len = range_end - range_start; // verife de l'ordre
	if (len <= 0) // recherche [Z-A] pas prise en compte ?
		return 0;
	else
		new_value = s_globbing_increment_range(range_start, range_end, len);

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
						(ft_isalnum((*concat)->value[i+2]))) // il y a une range
			{
				log_info("Is range:%s", ((*concat)->value+i));
				log_info("Value of len: %d",len);
				log_info("Value of i: %d",i);
				tmp_value_after_range = ft_strdup((*concat)->value + i + 3); // verifier ca
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
				log_info("(*concat)->value = %s", (*concat)->value);
		if ((*concat)->value[i])// && ft_isalnum((*concat)->value[i])) //Doit on check is allnum ?
		{
			log_info("Normal i=%d, char  = %c", i, (*concat)->value[i]);
			i++;
		}
	}
}
