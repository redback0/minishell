/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <bmilford@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:30:05 by bmilford          #+#    #+#             */
/*   Updated: 2024/09/04 19:36:28 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(char **argv)
{
	int		index;
	int		count;
	char	**env;

	(void)argv;
	index = 0;
	count = 0;
	env = ft_full_env();
	while (env[index] != NULL)
		index++;
	while (count <= index)
	{
		printf("%s\n", env[count]);
		count++;
	}
	return (0);
}
