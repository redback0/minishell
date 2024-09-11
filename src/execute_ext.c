/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:02:16 by njackson          #+#    #+#             */
/*   Updated: 2024/09/11 16:26:17 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command_child_ext(t_comm *comm);

int	execute_command(t_list *next_comm, int inpipe,
	t_list *comm_list, int status)
{
	t_comm	*comm;
	int		pipes[2];

	pipes[0] = -1;
	comm = (t_comm *)((next_comm)->content);
	if (comm->fdin < 0)
		comm->fdin = inpipe;
	else
		close(inpipe);
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
		execute_command_child(comm, comm_list, status);
	}
	close(comm->fdout);
	close(comm->fdin);
	return (pipes[0]);
}

void	execute_command_child(t_comm *comm, t_list *comm_list, int signal)
{
	struct sigaction	sa_sig_quit;

	sa_sig_quit.sa_handler = SIG_DFL;
	sigemptyset(&sa_sig_quit.sa_mask);
	sa_sig_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_sig_quit, NULL);
	if (!find_command(comm))
	{
		printf("Command not found: %s\n", comm->args[0]);
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(127);
	}
	open_redir_files(comm);
	if (is_builtin(comm) == 1)
		exit(execute_builtin_forked(comm, comm_list, signal));
	if (access(comm->command, X_OK) != 0)
	{
		perror(comm->command);
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(126);
	}
	execute_command_child_ext(comm);
}

static void	execute_command_child_ext(t_comm *comm)
{
	char	**envp;

	if (comm->fdout >= 0)
		dup2(comm->fdout, 1);
	if (comm->fdin >= 0)
		dup2(comm->fdin, 0);
	close(comm->fdout);
	close(comm->fdin);
	envp = ft_full_env();
	execve(comm->command, comm->args, envp);
	perror(comm->args[0]);
	exit(126);
}
