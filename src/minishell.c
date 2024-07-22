/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:01:53 by njackson          #+#    #+#             */
/*   Updated: 2024/07/22 18:45:29 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sig_interupt()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(void)
{
	struct sigaction	sa_sig_int;

	sa_sig_int.sa_handler = ms_sig_interupt;
	sigemptyset(&sa_sig_int.sa_mask);
	sigaction(SIGINT, &sa_sig_int, NULL);
	shell_loop();
}

void	shell_loop()
{
	char	*prompt;
	char	*line;

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
				exit(0);
			}
			printf("%s\n", line);
			free(line);
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
