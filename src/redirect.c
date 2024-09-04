/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:54:18 by njackson          #+#    #+#             */
/*   Updated: 2024/09/04 15:11:00 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*redirect_word(char *line)
{
	char	*out;
	int		i;
	int		start;

	start = 1;
	if (line[start] == *line)
		++start;
	while (line[start] == ' ')
		++start;
	i = start;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\'' || line[i] == '"')
			finish_quote(line, &i);
		else
			++i;
	}
	out = ft_substr(line, start, i - start);
	ft_strlcpy(line, line + i, i);
	return (out);
}

static void	set_redirect(t_comm *comm, char *line)
{
	char	*word;

	word = redirect_word(line);
	if (*line == '<')
	{
		if (comm->infile)
			free(comm->infile);
		comm->infile = word;
		comm->is_heredoc = line[0] == line[1]; // potentially run heredoc here?
	}
	else
	{
		if (comm->outfile)
			free(comm->outfile);
		comm->outfile = word;
		comm->is_append = line[0] == line[1];
	}
}

void	find_redirects(t_comm *comm, char *line)
{
	int		i;

	while (*line)
	{
		if (*line == '<' || *line == '>')
			set_redirect(comm, line);
		else if (*line == '\'' || *line == '"')
		{
			i = 0;
			finish_quote(line, &i);
			line += i;
		}
		else
			++line;
	}
}
