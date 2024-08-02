/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/08/02 15:32:39 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(char *line)
{
	char	**argv;
	char	**envp;
	int		i;

	i = 0;
	argv = get_cmd_args(line, &i);
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
	wait(NULL);
}

static void	finish_quote(char *line, int *i)
{
	int	s;

	if (line[*i] != '\'' && line[*i] != '"')
	{
		++(*i);
		return ;
	}
	s = (*i)++;
	while (line[*i] && line[*i] != line[s])
		++(*i);
}

char	**get_cmd_args(char *line, int *i)
{
	char	**args;
	int		argc;
	int		j;

	argc = 0;
	j = *i;
	while (line[j] && line[j] != '|')
	{
		while (line[j] && ft_isspace(line[j]))
			++j;
		if (line[j])
			argc++;
		while (line[j] && !ft_isspace(line[j]) && line[j] != '|')
			if (line[j] == '\'' || line[j] == '"')
				finish_quote(line, &j);
			else
				++j;
	}
	args = malloc((argc + 1) * sizeof(char *));
	argc = 0;
	while (line[*i] && line[*i] != '|')
	{
		if (!ft_isspace(line[*i]))
		{
			j = 0;
			while (line[*i + j] && !ft_isspace(line[*i + j]) && line[j] != '|' && line[j] != '<' && line[j] != '>')
				if (line[*i + j] == '\'' || line[*i + j] == '"')
					finish_quote(line + *i, &j);
				else
					++j;
			args[argc++] = ft_substr(line, *i, j);
			*i += j;
		}
		else
			++(*i);
	}
	args[argc] = 0;
	return (args);
}
