/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beefie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:33:34 by beefie            #+#    #+#             */
/*   Updated: 2024/09/04 19:27:04 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(char **argv)
{
	int	index;

	index = 0;
	while (argv)
		index++;
	if (index > 2)
	{
		printf("%s\n", "Error : too many arguements");
		return (1);
	}
	if (chdir(argv[2]) == -1)
	{
		perror(argv[1]);
		return (1);
	}
	else
	{
		//ft_set_env(PWD, );
		return(0);
	}
}
