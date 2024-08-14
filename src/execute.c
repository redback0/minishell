/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/08/14 17:26:46 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(char *line)
{
	static int			status = 0;
	struct sigaction	sa_sig_int;
	struct sigaction	sa_sig_ign;
	t_list				*comm_list;
	t_list				**next_comm;
	t_comm				*comm;

	comm_list = get_commands(line, status);
	free(line);
	execute_command(comm_list);
	sa_sig_ign.sa_handler = ms_sig_interupt_alt;
	sigemptyset(&sa_sig_ign.sa_mask);
	sa_sig_ign.sa_flags = 0;
	sigaction(SIGINT, &sa_sig_ign, &sa_sig_int);
	next_comm = &comm_list;
	while (*next_comm)
	{
		comm = (t_comm *)((*next_comm)->content);
		if (comm->pid > 0)
			waitpid(comm->pid, &(comm->raw_status), 0);
		next_comm = &((*next_comm)->next);
	}
	status = WEXITSTATUS(comm->raw_status);
	ft_lstclear(&comm_list, free_command);
	sigaction(SIGINT, &sa_sig_int, NULL);
}

void	execute_command(t_list *comm_list) // I need to pass fds here
// exit codes:
//  *command not found:			127
//  *command not executable:	126
//  *command execution failed:	126
{
	int		pipes[2];
	t_list	**next_comm;
	t_comm	*comm;

	next_comm = &comm_list;
	pipes[0] = -1;
	while (*next_comm)
	{
		comm = (t_comm *)((*next_comm)->content);
		comm->fdin = pipes[0];
		if ((*next_comm)->next)
		{
			pipe(pipes);
			comm->fdout = pipes[1];
		}
		comm->pid = fork();
		if (comm->pid < 0)
			printf("error: fork failed\n");
		else if (comm->pid == 0)
			execute_command_child(comm, comm_list);
		if (comm->fdout >= 0)
			close(comm->fdout);
		if (comm->fdin >= 0)
			close(comm->fdin);
		next_comm = &((*next_comm)->next);
	}
}

void	execute_command_child(t_comm *comm, t_list *comm_list)
{
	char	**envp;
	//char	*command;

	if (0) // find command
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
	// open redirect files here
	if (comm->fdout >= 0)
		dup2(comm->fdout, 1);
	if (comm->fdin >= 0)
		dup2(comm->fdin, 0);
	envp = ft_full_env();
	execve(comm->args[0], comm->args, envp); // replace this with below
	//execve(command, comm->args, envp);
	perror(comm->args[0]);
	exit(126);
}

/*
typedef struct s_comm
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		is_heredoc;
	int		is_append;
	int		fdin;
	int		pid;
	int		raw_status;
}	t_comm;
*/

t_list	*get_commands(char *line, int status)
{
	t_list	*comm_list;
	t_list	**end_comm_list;
	t_comm	*comm;
	char	**comm_lines;
	int		i;

	comm_lines = ms_split(line, '|');
	i = 0;
	end_comm_list = &comm_list;
	while (comm_lines[i])
	{
		comm = malloc(sizeof(*comm));
		ft_bzero(comm, sizeof(*comm));
		find_redirects(comm, line);
		comm->args = ms_split(comm_lines[i], ' ');
		variable_expand(comm->args, status);
		remove_quotes(comm->args);
		comm->fdin = -1;
		comm->fdout = -1;
		*end_comm_list = ft_lstnew(comm);
		end_comm_list = &((*end_comm_list)->next);
		++i;
	}
	ft_split_free(comm_lines, free);
	return (comm_list);
}

void	free_command(void *raw)
{
	t_comm *comm;

	comm = (t_comm *)raw;
	ft_split_free(comm->args, free);
	free(comm);
}
