/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:01:53 by njackson          #+#    #+#             */
/*   Updated: 2024/09/09 18:41:29 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal = 0;

int	main(int ac, char *av[], char *envp[])
{
	(void)ac, (void)av;
	init_signals();
	init_env(envp);
	shell_loop();
}

int	ms_exit(char **av, int status)
{
	int	exit_status;
	int	err;

	err = 0;
	exit_status = status;
	printf("exit\n");
	if (av && av[1])
	{
		exit_status = ft_atoi_strict(av[1], &err);
		if (err)
		{
			printf("exit: %s: numeric argument required\n", av[1]);
			exit_status = 2;
		}
		else if (av[2])
		{
			printf("exit: too many arguments\n");
			return (2);
		}
	}
	ft_clear_env();
	exit(exit_status);
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
			status = process_line(line, status);
		}
		else if (line)
			free(line);
		else
			ms_exit(NULL, status);
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
				i = ft_strlen(prompt);
			}
			j++;
		}
		else
			prompt[i++] = PS1[j++];
	}
	return (prompt);
}
