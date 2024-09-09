/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:12:10 by bmilford          #+#    #+#             */
/*   Updated: 2024/09/09 16:30:52 by bmilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export key=value ...
int	ms_export(char **argv)
{
	char	*value;
	int		index;
	char	*location;

	index = 1;
	while (argv[index])
	{
		location = ft_strchr(argv[index], '=');
		if (location != 0)
		{
			value = ft_strdup(location + 1);
			*location = '\0';
			ft_set_env(argv[index], value);
		}
		index++;
	}
	return (0);
}
