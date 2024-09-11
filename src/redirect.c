/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:54:18 by njackson          #+#    #+#             */
/*   Updated: 2024/09/11 16:36:52 by njackson         ###   ########.fr       */
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
	int		is_input;

	is_double = line[0] == line[1];
	is_input = *line == '<';
	word = redirect_word(line);
	if (is_input)
	{
		if (comm->infile)
			free(comm->infile);
		comm->infile = 0;
		if (is_double)
			comm->fdin = here_doc(word);
		else
			comm->infile = word;
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
			comm->fdout = open(comm->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (comm->is_append == 0)
			comm->fdout = open(comm->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
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
	int		word_len;

	word_len = ft_strlen(word);
	pipe(pipefd);
	line = get_next_line(0);
	while (line && !(ft_strncmp(line, word, word_len) == 0
			&& line[word_len] == '\n'))
	{
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (!line)
		printf("warning: here-document delimited by end-of-file\n");
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
