/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:01:53 by njackson          #+#    #+#             */
/*   Updated: 2024/06/12 14:28:06 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
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
