/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouvel <adrien.nouvel@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 14:54:47 by anouvel           #+#    #+#             */
/*   Updated: 2016/04/30 21:52:02 by anouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(int ac, const char *av[])
{
	logger_init(D_FATAL, "out.log");
	(void)av;
	(void)ac;
	logger_close();
	return (0);
}
