/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <bmilford@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:30:05 by bmilford          #+#    #+#             */
/*   Updated: 2024/09/09 18:49:14 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(char **argv)
{
	char	**env;
	int		index;

	(void)argv;
	index = 0;
	env = ft_full_env();
	while (env[index] != NULL)
	{
		printf("%s\n", env[index]);
		index++;
	}
	ft_split_free(env, free);
	return (0);
}
