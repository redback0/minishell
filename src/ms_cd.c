/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beefie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:33:34 by beefie            #+#    #+#             */
/*   Updated: 2024/08/12 19:17:24 by beefie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **argv)
{
	int	index;
	
	index = 0;
	while (argv)
		index++;
	if (ft_strncmp(argv[0], "cd", 3) != 0)
	{
		printf("%s\n", Error : command not found);
		return ;
	}
	if (index > 2)
	{
		printf("%s\n", Error : too many arguements);
		return ;
	}
	if (chdir(argv[2] == -1))
		perror(argv[1]);
	else
	{
		ft_set_env(PWD, );
		return(0);
	}
}
