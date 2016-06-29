/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnvhead64.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FNVHEAD64_H
# define FNVHEAD64_H

# define FNV_PRIME	((uint64_t)1099511628211)
# define FNV0_INIT	((t_fnv)0)
# define FNV1_INIT	((t_fnv)0xcbf29ce484222325ULL)

typedef uint64_t	t_fnv;

#endif
