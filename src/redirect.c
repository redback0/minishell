/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:54:18 by njackson          #+#    #+#             */
/*   Updated: 2024/09/09 16:48:51 by bmilford         ###   ########.fr       */
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
	int		is_double;

	is_double = line[0] == line[1];
	word = redirect_word(line);
	if (*line == '<')
	{
		if (comm->infile)
			free(comm->infile);
		comm->infile = word;
		if (is_double)
			comm->fdin = here_doc(word);
		comm->is_heredoc = is_double;
	}
	else
	{
		if (comm->outfile)
			free(comm->outfile);
		comm->outfile = word;
		comm->is_append = is_double;
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

void	open_redir_files(t_comm *comm)
{
	if (comm->outfile)
	{
		close(comm->fdout);
		if (comm->is_append == 1)
			comm->fdout = open(comm->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (comm->is_append == 0)
			comm->fdout = open(comm->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (comm->infile)
	{
		close(comm->fdin);
		if (comm->is_heredoc == 0)
			comm->fdin = open(comm->infile, O_RDONLY);
	}
}

int	here_doc(char *word)
{
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
	line = getnextline(0);
	while (ft_strncmp(line, word, -1) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = getnextline(0);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
