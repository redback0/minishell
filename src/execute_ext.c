/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:02:16 by njackson          #+#    #+#             */
/*   Updated: 2024/09/07 17:46:15 by bmilford         ###   ########.fr       */
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
	struct sigaction	sa_sig_quit;
	char				**envp;
	//char	*command;

	sa_sig_quit.sa_handler = SIG_DFL;
	sigemptyset(&sa_sig_quit.sa_mask);
	sa_sig_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_sig_quit, NULL);
	if (0) // find command -- if (find_command(comm->args[0]))
	{
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(127);
	}
	// open redirect files here
	open_redir_files(comm);
	if (is_builtin(comm) == 1)
		exit(execute_builtin(comm));
	if (access(comm->args[0], X_OK) != 0)
	{
		perror(comm->args[0]);
		//free(command);
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(126);
	}
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

int	is_builtin(t_comm *comm)
{
	if ((ft_strncmp(comm->args[0], "echo", -1) == 0)
		|| (ft_strncmp(comm->args[0], "cd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "pwd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "export", -1) == 0)
		|| (ft_strncmp(comm->args[0], "unset", -1) == 0)
		|| (ft_strncmp(comm->args[0], "env", -1) == 0))
		return (1);
	else
		return (0);
}

int	execute_builtin(t_comm *comm)
{
	if (ft_strncmp(comm->args[0], "echo", -1) == 0)
		return (ms_echo(comm->args));
	else if (ft_strncmp(comm->args[0], "cd", -1) == 0)
		return (ms_cd(comm->args));
	else if (ft_strncmp(comm->args[0], "pwd", -1) == 0)
		return (ms_pwd(comm->args));
//	else if (ft_strncmp(comm->args[0], "export", -1) == 0)
//		return (ms_export(comm->args));
//	else if (ft_strncmp(comm->args[0], "unset", -1) == 0)
//		return (ms_unset(comm->args));
	else if (ft_strncmp(comm->args[0], "env", -1) == 0)
		return (ms_env(comm->args));
	else
		return (127);
}

int	can_builtin_fork(t_comm *comm)
{
	if ((ft_strncmp(comm->args[0], "cd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "pwd", -1) == 0)
		|| (ft_strncmp(comm->args[0], "env", -1) == 0))
		return (1);
	else
		return (0);
}

int	execute_builtin_forked(t_comm *comm, t_list *comm_list)
{
	int	execute;

	if (comm->fdout >= 0)
		dup2(comm->fdout, 1);
	if (comm->fdin >= 0)
		dup2(comm->fdin, 0);
	close(comm->fdout);
	close(comm->fdin);
	execute = execute_builtin(comm);
	ft_lstclear(comm_list, free_command);
	ft_clear_env();
	return (execute);
}
	



