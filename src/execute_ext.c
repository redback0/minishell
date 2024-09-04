/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:02:16 by njackson          #+#    #+#             */
/*   Updated: 2024/09/04 19:11:49 by njackson         ###   ########.fr       */
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
	if (access(comm->args[0], X_OK) != 0)
	{
		perror(comm->args[0]);
		//free(command);
		ft_lstclear(&comm_list, free_command);
		ft_clear_env();
		exit(126);
	}
	// come back on 31/08
	if (is_builtin(comm->args) == 1)
		exit(execute_builtin(comm->args));
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

int	is_builtin(char **args)
{
	if ((ft_strchr(args, echo, -1) == 1) || (ft_strchr(args, cd, -1) == 1))
		return (1);
	else if ((ft_strchr(args, pwd, -1) == 1) || (ft_strchr(args, export, -1) == 1))
		return (1);
	else if ((ft_strchr(args, unset, -1) == 1) || (ft_strchr(args, env, -1) == 1))
		return (1);
	else
		return (0);
}

int	execute_builtin(char **argv)
{
	if (ft_strchr(arg, echo, -1) == 1)
		return (ms_echo(argv));
	else if (ft_strchr(arg, cd, -1) == 1)
		return (ms_cd(argv));
	else if (ft_strchr(arg, pwd, -1) == 1)
		return (ms_pwd(argv));
	else if (ft_strchr(arg, export, -1) == 1)
		return (ms_export(argv));
	else if (ft_strchr(arg, unset, -1) == 1)
		return (ms_unset(argv));
	else if (ft_strchr(arg, env, -1) == 1)
		return (ms_env(argv));
	else
		return (127);
}
