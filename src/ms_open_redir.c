/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_open_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmilford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:53:15 by bmilford          #+#    #+#             */
/*   Updated: 2024/09/04 19:07:11 by bmilford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_redir_files(t_comm *comm)
{
	if (comm->outfile)
	{
		close(comm->fdout);
		if (comm->is_append == 1)
			comm->fdout = open(comm->outfile, O_WRONLY | O_APPEND | O_CREATE, O644);
		if (comm->is_append == 0)
			comm->fdout = open(comm->outfile, O_WRONLY | O_TRUNC | O_CREATE, O644);
	}
	if (comm->infile)
	{
		close(comm->fdin);
		if (comm->is_heredoc == 1)
			comm->fdin = open(comm->infile,);
		else if (comm->is_heredoc == 0)
			comm->fdin = open(comm->infile, O_RDONLY);
	}
}	
