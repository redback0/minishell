/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:23:31 by bmilford          #+#    #+#             */
/*   Updated: 2024/09/11 16:33:18 by bmilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command(t_comm *comm)
{
	char	*command;

	if ((comm->args[0][0] == '/')
		|| (ft_strncmp("./", comm->args[0], 2) == 0)
		|| (ft_strncmp("../", comm->args[0], 3) == 0))
	{
		comm->command = comm->args[0];
		return (1);
	}
	if (is_builtin(comm) == 1)
		return (1);
	command = ft_strjoin("/", comm->args[0]);
	if (is_path(command, comm) == 1)
		return (1);
	return (0);
}

int	is_path(char *command, t_comm *comm)
{
	int		index;
	char	**path;
	char	*check;

	index = 0;
	path = ft_split(ft_get_env("PATH"), ':');
	while (path[index])
	{
		check = ft_strjoin(path[index], command);
		if (access(check, F_OK) == 0)
		{
			ft_split_free(path, free);
			free(command);
			comm->command = check;
			return (1);
		}
		free(check);
		index++;
	}
	return (0);
}
