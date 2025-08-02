/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:51:08 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/02 15:11:38 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_heredoc(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == 4)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	wait_all_child(void)
{
	int	status;
	int	last_exit;
	int	sig;

	last_exit = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig != SIGPIPE)
				last_exit = 128 + sig;
			if (sig == SIGINT)
				write(1, "\n", 1);
		}
	}
	setup_signals();
	return (last_exit);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
