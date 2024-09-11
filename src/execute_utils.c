/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:42:38 by njackson          #+#    #+#             */
/*   Updated: 2024/09/11 18:20:10 by njackson         ###   ########.fr       */
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

static int	get_word(const char *line, char c, char **out, size_t count)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != c)
	{
		if (line[i] == '\'' || line[i] == '"')
			finish_quote(line, &i);
		else
			++i;
	}
	out[count] = ft_substr(line, 0, i);
	if (!out)
	{
		while (count > 0)
			free(out[--count]);
		free(out);
		return (-1);
	}
	return (i);
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
			i = get_word(line, c, out, count);
			if (i < 0)
				return (0);
			line += i;
			count++;
		}
		else
			line++;
	}
	out[count] = 0;
	return (out);
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

void	free_command(void *raw)
{
	t_comm	*comm;

	comm = (t_comm *)raw;
	if (comm->command && comm->command != comm->args[0])
		free(comm->command);
	free(comm->infile);
	free(comm->outfile);
	ft_split_free(comm->args, free);
	free(comm);
}
