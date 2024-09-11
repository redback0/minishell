/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:30:59 by njackson          #+#    #+#             */
/*   Updated: 2024/09/11 15:02:04 by njackson         ###   ########.fr       */
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
	g_last_signal = signo;
	if (signo == SIGINT)
		printf("\n");
	else if (signo == SIGQUIT)
		printf("Quit\n");
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

void	swap_signal_for_execute(void)
{
	static struct sigaction	sa_sig_int = {};
	static struct sigaction	sa_sig_quit = {};
	struct sigaction		sa_sig_int_alt;
	struct sigaction		sa_sig_quit_alt;

	if (!sa_sig_int.sa_handler)
	{
		sa_sig_int.sa_handler = ms_sig_interupt_alt;
		sigemptyset(&sa_sig_int.sa_mask);
		sa_sig_int.sa_flags = 0;
		sa_sig_quit = sa_sig_int;
	}
	sigaction(SIGINT, &sa_sig_int, &sa_sig_int_alt);
	sigaction(SIGQUIT, &sa_sig_quit, &sa_sig_quit_alt);
	sa_sig_int = sa_sig_int_alt;
	sa_sig_quit = sa_sig_quit_alt;
}
