/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:26:43 by njackson          #+#    #+#             */
/*   Updated: 2024/09/11 16:35:12 by bmilford         ###   ########.fr       */
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

// in case that failed for whatever reason
# ifndef PS1
#  define PS1 "> "
# endif

# ifndef SPLASH
#  define SPLASH ""
# endif

// PATH_MAX, in case one didn't already exist
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

extern int	g_last_signal;

typedef struct s_comm
{
	char	*command;
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

int			ms_exit(char **av, int status);
char		*get_prompt(void);
void		shell_loop(void);
int			process_line(char *line, int status);
char		**shell_expand(t_list *args);
void		finish_quote(const char *line, int *i);
char		**ms_split(const char *line, char c);
int			execute_command(t_list *next_comm, int inpipe,
				t_list *comm_list, int status);
void		execute_line(t_list *comm_list, int status);
void		execute_command_child(t_comm *comm, t_list *comm_list, int status);
int			execute_single(t_list *comm_list, int status);
int			execute_wait(t_list *comm_list, int status);

void		find_redirects(t_comm *comm, char *line);
void		variable_expand(char **argv, int status);
void		remove_quotes(char **argv);
t_list		*get_commands(char *line, int status);
void		free_command(void *comm);
void		reverse_pipe(int infd, int outfd);
// signals
void		init_signals(void);
void		ms_sig_interupt(int signo);
void		ms_sig_interupt_alt(int signo);
void		swap_signal_for_execute(void);

// *********************** ASSIGNED TO BETH

int			is_builtin(t_comm *comm);
int			can_builtin_fork(t_comm *comm);
int			execute_builtin(t_comm *comm, int signal);
int			execute_builtin_forked(t_comm *comm, t_list *comm_list, int signal);

int			find_command(t_comm *command);
int			is_path(char *command, t_comm *comm);
// returns allocated the absolute path of a given command, NULL if there's no
// match. This will be called after checking for builtins

void		open_redir_files(t_comm *comm);
// opens the files at infile and outfile, and sets the fds to comm->fdin and
// fd->out.
//  if comm->is_heredoc is 1, run heredoc instead.
//  outfile can be truncate or append, depending on comm->is_append
//  if comm->fdin and/or comm->fdout is >= 0, close them before setting.

int			here_doc(char *word);
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
