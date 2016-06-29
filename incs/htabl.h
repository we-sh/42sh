/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABL_H
# define HTABL_H
# include "fnv.h"
# define HASH_TABLE_SIZE 5000

/*
** Struct related to path_init_hasht.c
*/

typedef struct			s_hasht
{
	char				*path;
	char				*name;
	struct s_hasht		*next;
}						t_hasht;

struct					s_body
{
	t_hasht				*head;
};

struct s_body bodies[HASH_TABLE_SIZE];

#endif
