/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:26:43 by njackson          #+#    #+#             */
/*   Updated: 2024/08/02 14:39:06 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# define _DEFAULT_SOURCE
// this is here cause vs code complains -- remove later, it's not needed for compiling


# include "libft.h"
# include "ft_env.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// moving this to a seperate header
# include "config.h"

typedef struct s_command
{
	char	**av;
	int		fdin;
	int		fdout;
}	t_command;

void		ms_exit();
char		*get_prompt(void);
void		shell_loop(void);
void		execute_line(char *line);
char		**get_cmd_args(char *line, int *i);

// signals
void		init_signals(void);
void		ms_sig_interupt(int signo);

// planned functions
void		run_command(t_command cmd);

// BUILTINS
// will we need to give these env? or will we be able to use getenv
// I think these will need to be more specific
int			ms_echo(int ac, char *av[]);
int			ms_cd(int ac, char *av[]);
int			ms_pwd(int ac, char *av[]);
int			ms_export(int ac, char *av[]);
int			ms_unset(int ac, char *av[]);
int			ms_env(int ac, char *av[]);
// this can send a signal to the main process to tell it to exit. I think

#endif
