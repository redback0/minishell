/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beefie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:33:34 by beefie            #+#    #+#             */
/*   Updated: 2024/09/09 17:01:59 by bmilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(char **argv)
{
	int	index;

	index = 0;
	while (argv[index])
		index++;
	if (index != 2)
	{
		printf("%s\n", "Error : Wrong number of arguements");
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		perror(argv[1]);
		return (1);
	}
	else
		return (0);
}
