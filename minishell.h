/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:26:43 by njackson          #+#    #+#             */
/*   Updated: 2024/07/23 14:55:57 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// moving this to a seperate header
# include "config.h"

typedef struct s_ms_dat
{
	char	**env;
	char	*prompt;
	// DEFINITELY MORE STUFF, I'LL WORK OUT WHAT LATER
}	t_ms_dat;

typedef struct s_command
{
	char	*cmd;
	char	**av;
	int		fdin;
	int		fdout;
}	t_command;

t_command	*tokenizer(char *line, t_ms_dat ms);
void		run_command(t_command cmd, t_ms_dat ms);
// this might need a different type
char		*get_prompt(void);
void		shell_loop(void);

// BUILTINS
// will we need to give these env? or will we be able to use getenv
// I think these will need to be more specific
int			ms_echo(int ac, char *av[]);
int			ms_cd(int ac, char *av[]);
int			ms_pwd(int ac, char *av[]);
int			ms_export(int ac, char *av[]);
int			ms_unset(int ac, char *av[]);
int			ms_env(int ac, char *av[]);
int			ms_exit();
// this can send a signal to the main process to tell it to exit. I think

#endif
