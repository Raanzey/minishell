/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:23:06 by musisman          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:29 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == 0 || g_signal == 3)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 3;
	}
	else if (g_signal == 1)
	{
		write(1, "\n", 1);
		ft_free();
		exit(130);
	}
	else if (g_signal == 2)
	{
		write(1, "\n", 1);
		ft_free();
		exit(130);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	discard_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void sigquit_handler(int sig)
{
	(void)sig;
	write(1, "Quit\n", 5); // veya hiç yazma
	ft_free();
	exit(131); // SIGQUIT 3 → 128+3 = 131
}
