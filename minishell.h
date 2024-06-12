/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:26:43 by njackson          #+#    #+#             */
/*   Updated: 2024/06/12 14:32:31 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef PS1
#  define PS1 "minishell \e[38;2;187;0;0m%p\x1b[0m $> "
# endif

typedef struct s_msh_dat
{
	char	**env;
	char	*prompt;
	// DEFINITELY MORE STUFF, I'LL WORK OUT WHAT LATER
}	t_msh_dat;

typedef struct s_command
{
	char	*cmd;
	char	**av;
	int		fdin;
	int		fdout;
}	t_command;

t_command	*tokenizer(char *line, t_msh_dat msh);
void		run_command(t_command cmd, t_msh_dat msh);
// this might need a different type
char		*get_prompt(void);

// BUILTINS
// will we need to give these env? or will we be able to use getenv
int			msh_echo(int ac, char *av[]);
int			msh_cd(int ac, char *av[]);
int			msh_pwd(int ac, char *av[]);
int			msh_export(int ac, char *av[]);
int			msh_unset(int ac, char *av[]);
int			msh_env(int ac, char *av[]);
int			msh_exit(int ac, char *av[]);
// this can send a signal to the main process to tell it to exit. I think

#endif
