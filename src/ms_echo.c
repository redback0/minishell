/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beefie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:11:56 by beefie            #+#    #+#             */
/*   Updated: 2024/09/04 19:23:29 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(char **argv)
{
	int	index;
	int	new;

	new = 0;
	index = 1;
	if (ft_strncmp(argv[1], "-n", 3) != 0)
	{
		new = 1;
		index++;
	}
	while (index)
	{
		printf("%s ", argv[index]);
		index++;
		if (!argv[index])
			break ;
	}
	if (new == 0)
		printf("%s\n", argv[index]);
	else
		printf("%s", argv[index]);
	return (0);
}
