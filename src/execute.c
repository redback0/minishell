/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/08/09 00:19:52 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(char *line)
{
	struct sigaction	sa_sig_int;
	struct sigaction	sa_sig_ign;
	char				**comms;
	int					raw_status;
	int					i;
	int					num_pids;
	int					*pid;

	comms = ms_split(line, '|');
	num_pids = -1;
	while (comms[++num_pids])
		;
	pid = malloc(num_pids * sizeof(int));
	i = -1;
	while (comms && comms[++i])
		pid[i] = execute_command(comms[i]);
	sa_sig_ign.sa_handler = ms_sig_interupt_alt;
	sigemptyset(&sa_sig_ign.sa_mask);
	sa_sig_ign.sa_flags = 0;
	sigaction(SIGINT, &sa_sig_ign, &sa_sig_int);
	i = 0;
	while (i < num_pids)
	{
		if (pid[i] > 0)
			waitpid(pid[i], &raw_status, 0);
		i++;
	}
	ft_set_env("?", ft_itoa(WEXITSTATUS(raw_status)));
	ft_split_free(comms, free);
	free(pid);
	sigaction(SIGINT, &sa_sig_int, NULL);
}

int	execute_command(char *comm) // I need to pass fds here
// exit codes:
//  *command not found:			127
//  *command not executable:	126
//  *fork failed				unsure
{
	char	**argv;
	char	**envp;
	int		pid;

	argv = ms_split(comm, ' ');
	variable_expand(argv);
	remove_quotes(argv);
	pid = fork();
	if (pid < 0)
		printf("error: fork failed\n");
	else if (pid == 0)
	{
		if (access(argv[0], X_OK) != 0)
		{
			perror(argv[0]);
			ft_split_free(argv, free);
			exit(126);
		}
		envp = ft_full_env();
		execve(argv[0], argv, envp);
		perror("error");
		exit(126); // I don't know what this error code should be
	}
	ft_split_free(argv, free);
	return (pid);
}
