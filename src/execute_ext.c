/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:02:16 by njackson          #+#    #+#             */
/*   Updated: 2024/09/03 17:36:51 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_list *next_comm, int inpipe, t_list *comm_list)
{
	t_comm	*comm;
	int		pipes[2];

	pipes[0] = -1;
	comm = (t_comm *)((next_comm)->content);
	comm->fdin = inpipe;
	if ((next_comm)->next)
	{
		pipe(pipes);
		comm->fdout = pipes[1];
	}
	comm->pid = fork();
	if (comm->pid < 0)
		printf("error: fork failed\n");
	else if (comm->pid == 0)
	{
		close(pipes[0]);
		execute_command_child(comm, comm_list);
	}
	if (comm->fdout >= 0)
		close(comm->fdout);
	if (comm->fdin >= 0)
		close(comm->fdin);
	return (pipes[0]);
}

void	execute_command_child(t_comm *comm, t_list *comm_list)
{
	char	**envp;
	//char	*command;

	if (0) // find command -- if (find_command(comm->args[0]))
	{
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(127);
	}
	if (access(comm->args[0], X_OK) != 0)
	{
		perror(comm->args[0]);
		//free(command);
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(126);
	}
	// come back on 31/08
	// open redirect files here
	if (comm->fdout >= 0)
		dup2(comm->fdout, 1);
	if (comm->fdin >= 0)
		dup2(comm->fdin, 0);
	close(comm->fdout);
	close(comm->fdin);
	envp = ft_full_env();
	execve(comm->args[0], comm->args, envp); // replace this with below
	//execve(command, comm->args, envp);
	perror(comm->args[0]);
	exit(126);
}
