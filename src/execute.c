/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:13:13 by njackson          #+#    #+#             */
/*   Updated: 2024/08/05 13:01:55 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(char *line)
{
	char	**argv;
	char	**envp;
	int		i;

	i = 0;
	argv = shell_expand(get_cmd_args(line, &i));
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

t_list	*get_cmd_args(char *line, int *i)
{
	t_list	*args;
	t_list	**alast;
	int		argc;
	int		j;

	alast = &args;
	while (line[*i] && line[*i] != '|')
	{
		if (!ft_isspace(line[*i]))
		{
			j = 0;
			while (line[*i + j] && !ft_isspace(line[*i + j]) && line[j] != '|')
				if (line[*i + j] == '\'' || line[*i + j] == '"')
					finish_quote(line + *i, &j);
				else
					++j;
			alast->content = ft_substr(line, *i, j);
			alast = &((*args)->next);
			*i += j;
		}
		else
			++(*i);
	}
	return (args);
}

t_command	*shell_expand(t_list *args)
{
	t_command	*comm;
	t_list		**next;
	char		*cont;
	int			cont_i;
	int			arg_len;
	int			argc;

	comm->infd = 0;
	comm->outfd = 0;
	next = &args;
	argc = 0;
	while (*next)
	{
		if (*((char *)(*next)->content) != '<'
			&& *((char *)(*next)->content) != '>')
			argc++;
		else if (!*((char *)(*next)->content + 1))
			argc--;
		next = &((*next)->next);
	}
	comm = malloc(sizeof(comm));
	comm->av = malloc((argc + 1) * sizeof(char *));
	next = &args;
	while (*next)
	{
		cont = (*next)->content;
		cont_i = 0;
		arg_len = 0;
		while (cont[cont_i])
		{
			if (*cont == '\'' || *cont == '"')
				finish_quote(cont, &cont_i); // need to get how many characters removed
			else if (*cont == '<')
				// infd
			else if (*cont == '>')
				// outfd
		}
	}
}
