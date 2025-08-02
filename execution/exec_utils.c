/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:03:32 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:27 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_pipe_or_die(t_command *cmd, int pipe_fd[2])
{
	if (cmd->next && pipe(pipe_fd) == -1)
		free_and_exit(err_exp("pipe: ", 0, 1, 1));
}

int	open_redir_fd(t_redirect *redir)
{
	int	fd;

	if (redir->type == 1)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == 2)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == 3)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == 4)
		fd = redir->fd;
	else
		fd = -1;
	return (fd);
}

void	dup_redir_fd(t_redirect *redir, int fd)
{
	if (fd == -1)
		return ;
	if (redir->type == 3 || redir->type == 4)
		dup2(fd, STDIN_FILENO);
	else if (redir->type == 1 || redir->type == 2)
		dup2(fd, STDOUT_FILENO);
}

void	handle_redirections(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->redir;
	while (redir)
	{
		fd = open_redir_fd(redir);
		if ((redir->type == 1 || redir->type == 2 || redir->type == 3)
			&& fd == -1)
		{
			err_exp(redir->filename, 0, 1, 1);
			free_and_exit(1);
		}
		dup_redir_fd(redir, fd);
		redir = redir->next;
	}
}

char	*handle_path(t_command *cmd, t_env **env_list)
{
	struct stat	st;
	char		*path;

	if (!ft_strcmp(cmd->av[0], ".") || !ft_strcmp(cmd->av[0], ".."))
		error(0, cmd->av[0], ERR_CMD, 127);
	else if (ft_strchr(cmd->av[0], '/'))
	{
		if (access(cmd->av[0], F_OK) != 0)
			error(0, cmd->av[0], ERR_CD, 127);
		else if (access(cmd->av[0], X_OK) != 0)
			error(0, cmd->av[0], ERR_PRM, 126);
		else if (stat(cmd->av[0], &st) == 0 && S_ISDIR(st.st_mode))
			error(0, cmd->av[0], ERR_DIC, 126);
		else
			return (ft_strdup(cmd->av[0]));
	}
	else
	{
		path = find_path(cmd->av[0], *env_list);
		if (!path)
			error(0, cmd->av[0], ERR_CMD, 127);
		return (path);
	}
	return (NULL);
}
