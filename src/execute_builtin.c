/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:44:58 by njackson          #+#    #+#             */
/*   Updated: 2024/09/09 18:28:16 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_comm *comm)
{
	if ((ft_strncmp(comm->args[0], "echo", -1) == 0)
		|| (ft_strncmp(comm->args[0], "cd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "pwd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "export", -1) == 0)
		|| (ft_strncmp(comm->args[0], "unset", -1) == 0)
		|| (ft_strncmp(comm->args[0], "env", -1) == 0)
		|| (ft_strncmp(comm->args[0], "exit", -1) == 0))
		return (1);
	else
		return (0);
}

int	can_builtin_fork(t_comm *comm)
{
	if ((ft_strncmp(comm->args[0], "echo", -1) == 0)
		|| (ft_strncmp(comm->args[0], "pwd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "env", -1) == 0))
		return (1);
	else
		return (0);
}

int	execute_builtin(t_comm *comm, int status)
{
	if (ft_strncmp(comm->args[0], "echo", -1) == 0)
		return (ms_echo(comm->args));
	else if (ft_strncmp(comm->args[0], "cd", -1) == 0)
		return (ms_cd(comm->args));
	else if (ft_strncmp(comm->args[0], "pwd", -1) == 0)
		return (ms_pwd(comm->args));
	else if (ft_strncmp(comm->args[0], "export", -1) == 0)
		return (ms_export(comm->args));
	else if (ft_strncmp(comm->args[0], "unset", -1) == 0)
		return (ms_unset(comm->args));
	else if (ft_strncmp(comm->args[0], "env", -1) == 0)
		return (ms_env(comm->args));
	else if (ft_strncmp(comm->args[0], "exit", -1) == 0)
		return (ms_exit(comm->args, status));
	else
		return (127);
}

int	execute_builtin_forked(t_comm *comm, t_list *comm_list, int status)
{
	int	execute;

	if (comm->fdout >= 0)
		dup2(comm->fdout, 1);
	if (comm->fdin >= 0)
		dup2(comm->fdin, 0);
	close(comm->fdout);
	close(comm->fdin);
	execute = execute_builtin(comm, status);
	ft_lstclear(&comm_list, free_command);
	ft_clear_env();
	return (execute);
}
