/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/09/11 16:08:56 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_line(char *line, int status)
{
	t_list				*comm_list;

	comm_list = get_commands(line, status);
	free(line);
	if (!((t_comm *)(comm_list->content))->args[0])
	{
		ft_lstclear(&comm_list, free_command);
		return (status);
	}
	if (ft_lstsize(comm_list) == 1)
		return (execute_single(comm_list, status));
	execute_line(comm_list, status);
	return (execute_wait(comm_list, status));
}

int	execute_wait(t_list *comm_list, int status)
{
	t_list				**next_comm;
	t_comm				*comm;

	swap_signal_for_execute();
	g_last_signal = 0;
	next_comm = &comm_list;
	while (*next_comm)
	{
		comm = (t_comm *)((*next_comm)->content);
		if (comm->pid > 0)
			waitpid(comm->pid, &(comm->raw_status), 0);
		next_comm = &((*next_comm)->next);
	}
	status = WEXITSTATUS(comm->raw_status);
	if (g_last_signal)
		status = g_last_signal + 128;
	ft_lstclear(&comm_list, free_command);
	swap_signal_for_execute();
	return (status);
}

int	execute_single(t_list *comm_list, int status)
{
	t_comm	*comm;

	comm = (t_comm *)comm_list->content;
	if (is_builtin(comm) && !can_builtin_fork(comm))
	{
		status = execute_builtin(comm, status);
		ft_lstclear(&comm_list, free_command);
		return (status);
	}
	execute_line(comm_list, status);
	return (execute_wait(comm_list, status));
}

void	execute_line(t_list *comm_list, int status) // I need to pass fds here
// exit codes:
//  *command not found:			127
//  *command not executable:	126
//  *command execution failed:	126
{
	int		inpipe;
	t_list	**next_comm;

	next_comm = &comm_list;
	inpipe = -1;
	while (*next_comm)
	{
		inpipe = execute_command(*next_comm, inpipe, comm_list, status);
		next_comm = &((*next_comm)->next);
	}
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
		comm->fdin = -1;
		comm->fdout = -1;
		find_redirects(comm, comm_lines[i]);
		comm->args = ms_split(comm_lines[i], ' ');
		variable_expand(comm->args, status);
		remove_quotes(comm->args);
		*end_comm_list = ft_lstnew(comm);
		end_comm_list = &((*end_comm_list)->next);
		++i;
	}
	ft_split_free(comm_lines, free);
	return (comm_list);
}
