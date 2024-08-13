/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:26:43 by njackson          #+#    #+#             */
/*   Updated: 2024/08/13 18:20:14 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_env.h"
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// PS1 and SPLASH defined here
# include "config.h"

typedef struct s_comm
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		is_heredoc;
	int		is_append;
	int		fdin;
	int		fdout;
	int		pid;
	int		raw_status;
}	t_comm;

void		ms_exit(void);
char		*get_prompt(void);
void		shell_loop(void);
void		execute_line(char *line);
char		**shell_expand(t_list *args);
void		finish_quote(const char *line, int *i);
char		**ms_split(const char *line, char c);
int			execute_command(t_comm *comm, t_list *comm_list);
void		find_redirects(t_comm *comm, char *line);
void		variable_expand(char **argv, int status);
void		remove_quotes(char **argv);
t_list		*get_commands(char *line, int status);
void		free_command(void *comm);

// signals
void		init_signals(void);
void		ms_sig_interupt(int signo);
void		ms_sig_interupt_alt(int signo);

// *********************** ASSIGNED TO BETH

char		*find_command(char *command);
// returns allocated the absolute path of a given command, NULL if there's no
// match. This will be called after checking for builtins

// BUILTINS
// will we need to give these env? or will we be able to use getenv
// I think these will need to be more specific
int			ms_echo(char **av);
int			ms_cd(char **av);
int			ms_pwd(char **av);
int			ms_export(char **av);
int			ms_unset(char **av);
int			ms_env(char **av);
// this can send a signal to the main process to tell it to exit. I think

#endif
