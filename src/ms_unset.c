/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:25:56 by bmilford          #+#    #+#             */
/*   Updated: 2024/09/09 17:06:37 by bmilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(char **argv)
{
	int	index;

	index = 0;
	while (argv[index])
	{
		ft_unset_env(argv[index]);
		index++;
	}
	return (0);
}
