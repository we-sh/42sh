/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnvhead32.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FNVHEAD32_H
# define FNVHEAD32_H

# define FNV_PRIME	((uint32_t)16777619)
# define FNV0_INIT	((t_fnv)0)
# define FNV1_INIT	((t_fnv)0x811c9dc5)

typedef uint32_t	t_fnv;

#endif
