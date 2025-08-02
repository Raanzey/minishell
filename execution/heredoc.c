/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:06:34 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:58:00 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_heredoc_loop(t_redirect *redir, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, redir->filename,
					ft_strlen(redir->filename))
				&& line[ft_strlen(redir->filename)] == '\0'))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
}

int	handle_heredoc_child(t_redirect *redir, int *fd)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	setup_signals();
	handle_heredoc_loop(redir, fd);
	close(fd[1]);
	return (free_and_exit(0));
}

static int	handle_single_heredoc(t_redirect *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (err_noext("pipe", 0, 1, 1));
	discard_signals();
	g_signal = 2;
	pid = fork();
	if (pid == -1)
		return (err_noext("fork", 0, 1, 1));
	if (pid == 0)
		handle_heredoc_child(redir, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	redir->fd = fd[0];
	return (0);
}

int	handle_heredocs(t_redirect *redir)
{
	int	res;

	while (redir)
	{
		if (redir->type == 4)
		{
			res = handle_single_heredoc(redir);
			if (res != 0)
				return (res);
		}
		redir = redir->next;
	}
	return (0);
}

int	has_output_redir(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == 1 || redir->type == 2)
			return (1);
		redir = redir->next;
	}
	return (0);
}
