/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:42:38 by njackson          #+#    #+#             */
/*   Updated: 2024/08/08 14:00:44 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ms_split_alloc(const char *line, char c)
{
	size_t	i;
	size_t	count;

	if (!line)
		return (0);
	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && line[i] == c)
			i++;
		if (line[i] && line[i] != c)
			count++;
		while (line[i] && line[i] != c)
			i++;
	}
	return (malloc((count + 1) * sizeof(char *)));
}

char	*get_word(const char *line, int *i, char c, char **out)
{
	while (line[*i] && line[*i] != c)
	{
		if (line[*i] == '\'' || line[*i] == '"')
			finish_quote(line, i);
		else
			++(*i);
	}
	return (*out = ft_substr(line, 0, *i));
}


char	**ms_split(const char *line, char c)
{
	char	**out;
	int		i;
	size_t	count;

	out = ms_split_alloc(line, c);
	if (!out)
		return (0);
	count = 0;
	while (*line)
	{
		if (*line != c)
		{
			i = 0;
			if (!get_word(line, &i, c, &(out[count])))
			{
				while (count > 0)
					free (out[--count]);
				free(out);
				return (0);
			}
			line += i;
			count++;
		}
		else
			line++;
	}
	out[count] = 0;
	return (out);
}
