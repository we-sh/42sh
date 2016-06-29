/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	option_free(t_option **opt)
{
	ft_memdel((void **)&(*opt)->value);
	ft_memdel((void **)&(*opt));
	*opt = NULL;
}
