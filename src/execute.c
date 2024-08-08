/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/08/08 13:47:34 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	execute_line(char *line)
{
	struct sigaction	sa_sig_int;
	struct sigaction	sa_sig_ign;
	char				**comms;
	int					i;

	comms = ms_split(line, '|');
	i = -1;
	while (comms && comms[++i])
		execute_command(comms[i]); // I think I'll have to keep track of PIDs here for when I wait at the end
	ft_split_free(comms, free);
	sa_sig_ign.sa_handler = ms_sig_interupt_alt;
	sigemptyset(&sa_sig_ign.sa_mask);
	sa_sig_ign.sa_flags = 0;
	sigaction(SIGINT, &sa_sig_ign, &sa_sig_int);
	wait(&g_status);
	sigaction(SIGINT, &sa_sig_int, NULL);
}

void	execute_command(char *comm) // I need to pass fds here
{
	char	**argv;
	char	**envp;

	argv = ms_split(comm, ' ');
	variable_expand(argv);
	remove_quotes(argv);
	if (access(argv[0], X_OK) != 0)
	{
		printf("%s: Permission denied\n", argv[0]);
		ft_split_free(argv, free);
		return ;
	}
	if (fork() == 0)
	{
		envp = ft_full_env();
		execve(argv[0], argv, envp);
		perror("error");
		exit(1);
	}
	ft_split_free(argv, free);
}

void	variable_expand(char **argv)
{
	int		i;
	int		j;
	char	*old_arg;
	char	*var;

	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] == '\'')
				finish_quote(*argv, &i);
			else if ((*argv)[i++] == '$')
			{
				old_arg = *argv;
				j = 0;
				if (!ft_isdigit(old_arg[i]))
					while (ft_isalnum((old_arg)[i + j])
						|| (old_arg)[i + j] == '_')
						++j;
				var = ft_get_env(old_arg + i);
				(*argv)[i - 1] = 0;
				*argv = ft_strnjoin(3, old_arg, var, old_arg + i + j);
				free(old_arg);
				i += ft_strlen(var) - 1;
			}
		}
		++argv;
	}
}

void	remove_quotes(char **argv)
{
	int		j;
	int		i;
	char	*new_arg_parts[3];

	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] == '\'' || (*argv)[i] == '"')
			{
				new_arg_parts[0] = *argv;
				new_arg_parts[1] = *argv + i + 1;
				j = 0;
				finish_quote(*argv + i, &j);
				if (j > 1 && (*argv)[i + j - 1] == (*argv)[i])
				{
					new_arg_parts[2] = *argv + i + j;
					(*argv)[i] = 0;
					(*argv)[i + j - 1] = 0;
					*argv = ft_strnjoin(3, new_arg_parts[0], new_arg_parts[1], new_arg_parts[2]);
					free(new_arg_parts[0]);
					i += j - 3;
				}
			}
			++i;
		}
		++argv;
	}
}

void	finish_quote(const char *line, int *i)
{
	int	s;

	if (line[*i] != '\'' && line[*i] != '"')
	{
		++(*i);
		return ;
	}
	s = *i;
	++(*i);
	while (line[*i] && line[*i] != line[s])
		++(*i);
	if (line[*i] != '\0')
		++*i;
	else
		*i = s + 1;

}
