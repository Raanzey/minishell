/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:00:13 by musisman          #+#    #+#             */
/*   Updated: 2025/06/03 12:00:13 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_unexpected_token(char *token)
{
	if (!token || *token == '\0')
		return (printf("syntax error near unexpected token `newline'\n"), 1);
	return (printf("syntax error near unexpected token `%s'\n", token), 1);
}

int	ambiguous_redirect_error(t_command *cmd)
{
	t_redirect	*redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->filename && redir->filename[0] == '\0')
			{
				printf("minishell: ambiguous redirect\n");
				return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	pipe_error(t_command *cmd)
{
	if (!cmd)
		return (print_unexpected_token("|"));
	while (cmd)
	{
		if (!cmd->av || !cmd->av[0])
			return (print_unexpected_token("|"));
		cmd = cmd->next;
	}
	return (0);
}

int	redir_error(t_command *cmd)
{
	t_redirect	*redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (!redir->filename || redir->filename[0] == '\0')
				return (print_unexpected_token("newline"));
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	handle_error(t_command *cmd)
{
	if (pipe_error(cmd))
		return (1);
	if (redir_error(cmd))
		return (1);
	if (ambiguous_redirect_error(cmd))
		return (1);
	return (0);
}
