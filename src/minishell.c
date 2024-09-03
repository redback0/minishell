/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:01:53 by njackson          #+#    #+#             */
/*   Updated: 2024/09/03 15:40:28 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	(void)ac, (void)av;
	init_signals();
	init_env(envp);
	shell_loop();
}

void	ms_exit(void)
{
	ft_clear_env();
	exit(0);
}

void	shell_loop(void)
{
	int		status;
	char	*prompt;
	char	*line;

	status = 0;
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (line && *line)
		{
			add_history(line);
			if (ft_strncmp(line, "exit", 5) == 0)
			{
				free(line);
				ms_exit();
			}
			status = process_line(line, status);
		}
		else if (line)
		{
			free(line);
		}
		else
		{
			printf("exit\n");
			ms_exit();
		}
	}
}

char	*get_prompt(void)
{
	char	*prompt;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(PS1) + 128;
	prompt = (char *)ft_calloc(size, sizeof(char));
	i = 0;
	j = 0;
	while (i < size - 1)
	{
		if (PS1[j] == '%')
		{
			if (PS1[++j] == 'p')
			{
				getcwd(prompt + i, size - i);
				i = strlen(prompt);
			}
			j++;
		}
		else
			prompt[i++] = PS1[j++];
	}
	return (prompt);
}
