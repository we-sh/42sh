/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node__option_alloc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list			*list_node__option_alloc(t_option const *option_ref,
					char **argv, size_t i)
{
	t_option	*option;

	if ((option = malloc(sizeof(t_option))) == NULL)
		return (NULL);
	option->index = option_ref->index;
	option->name = option_ref->name;
	option->is_single_char = option_ref->is_single_char;
	option->has_value = option_ref->has_value;
	option->value_is_numeric = option_ref->value_is_numeric;
	option->value_is_alnum = option_ref->value_is_alnum;
	option->value = NULL;
	if (option_ref->has_value == 1)
		if ((option->value = ft_strdup(argv[i + 1])) == NULL)
			return (NULL);
	return (&option->list_option);
}
