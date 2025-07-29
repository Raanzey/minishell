/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:06:34 by musisman          #+#    #+#             */
/*   Updated: 2025/07/29 19:39:44 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_delimiter(char *line, char *delim, int has_cmd)
{
	return ((!line || (!ft_strncmp(line, delim, ft_strlen(delim))
				&& line[ft_strlen(delim)] == '\0')) && !has_cmd);
}

static void	handle_heredoc_loop(t_redirect *redir, int *fd, int has_cmd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line) // SIGINT durumunda readline NULL döner
		{
			//write(1, "\n", 1);  // prompt hizasını düzelt
			break ;
		}
		if (is_delimiter(line, redir->filename, has_cmd))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		//free(line);
	}
}


void	handle_heredocs(t_redirect *redir, int has_cmd)
{
	int	fd[2];

	while (redir)
	{
		if (redir->type == 4)
		{
			if (pipe(fd) == -1)
				exit(err_exp("pipe", 0, 1, 1));
			// g_signal = 2;
			setup_signals();
			handle_heredoc_loop(redir, fd, has_cmd);
			close(fd[1]);
			redir->fd = fd[0]; // 🔴 heredoc’un read-end’ini sakla
		}
		redir = redir->next;
	}
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
