/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/07/31 18:57:03 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char *line)
{
	char	**argv;
	char	**envp;

	if (access(line, X_OK) != 0)
	{
		printf("%s\n", line);
		return ;
	}
	if (fork() == 0)
	{
		argv = malloc(2 * sizeof(char *));
		argv[0] = ft_strdup(line);
		argv[1] = 0;
		envp = ft_full_env();
		execve(line, argv, envp);
		perror("error");
		exit(1);
	}
	wait(NULL);
}
