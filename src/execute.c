/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/08/13 18:33:56 by njackson         ###   ########.fr       */
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
	int					outfd;

	comm_list = get_commands(line, status);
	free(line);
	next_comm = &comm_list;
	outfd = -1;
	while (*next_comm)
	{
		outfd = execute_command((t_comm *)((*next_comm)->content), comm_list);
		if ((*next_comm)->next)
			((t_comm *)((*next_comm)->next->content))->fdin = dup(outfd);
		if (((t_comm *)((*next_comm)->content))->outfile
			|| (*next_comm)->next)
		{
			close(outfd);
			outfd = -1;
		}
		next_comm = &((*next_comm)->next);
	}
	if (outfd >= 0)
	{
		// output to stdout
	}
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

int	execute_command(t_comm *comm, t_list *comm_list) // I need to pass fds here
// exit codes:
//  *command not found:			127
//  *command not executable:	126
//  *command execution failed:	126
{
	char	**envp;
	int		pipes[2];

	if (!pipe(pipes))
		printf("error: pipe failed\n");
	comm->pid = fork();
	if (comm->pid < 0)
		printf("error: fork failed\n");
	else if (comm->pid == 0)
	{
		if (access(comm->args[0], X_OK) != 0)
		{
			perror(comm->args[0]);
			ft_lstclear(&comm_list, free_command);
			ft_clear_env();
			exit(126);
		}
		envp = ft_full_env();
		execve(comm->args[0], comm->args, envp);
		perror(comm->args[0]);
		exit(126); // I don't know what this error code should be
	}
	close(pipes[1]);
	return (pipes[0]);
}

/*
typedef struct s_comm
{
	char	**args;
	int		fdin;
	int		fdout;
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
