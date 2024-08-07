/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:30:59 by njackson          #+#    #+#             */
/*   Updated: 2024/08/05 18:16:33 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sig_interupt(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ms_sig_interupt_alt(int signo)
{
	(void)signo;
	printf("\n");
}

void	init_signals(void)
{
	struct sigaction	sa_sig_int;
	struct sigaction	sa_sig_quit;

	sa_sig_int.sa_handler = ms_sig_interupt;
	sigemptyset(&sa_sig_int.sa_mask);
	sa_sig_int.sa_flags = 0;
	sigaction(SIGINT, &sa_sig_int, NULL);
	sa_sig_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sig_quit.sa_mask);
	sa_sig_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_sig_quit, NULL);
	printf("%s", SPLASH);
}
