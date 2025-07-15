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

int	redir_error(t_command *cmd)
{
	t_redirect	*redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (!redir->filename)
				return (print_unexpected_token("newline"));
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	handle_error(t_command *cmd)
{
	if (redir_error(cmd))
		return (1);
	if (ambiguous_redirect_error(cmd))
		return (1);
	return (0);
}

int	pre_parser_error(char **tokens, int i)
{
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
		{
			if (i == 0 || !tokens[i + 1] || !ft_strncmp(tokens[i + 1], "|", 2))
				return (print_unexpected_token("|"));
		}
		else if (!ft_strncmp(tokens[i], "<", 2)
			|| !ft_strncmp(tokens[i], ">", 2)
			|| !ft_strncmp(tokens[i], "<<", 3)
			|| !ft_strncmp(tokens[i], ">>", 3))
		{
			if (!tokens[i + 1])
				return (print_unexpected_token("newline"));
			if (!ft_strncmp(tokens[i + 1], "<", 2)
				|| !ft_strncmp(tokens[i + 1], ">", 2)
				|| !ft_strncmp(tokens[i + 1], "<<", 3)
				|| !ft_strncmp(tokens[i + 1], ">>", 3)
				|| !ft_strncmp(tokens[i + 1], "|", 2))
				return (print_unexpected_token(tokens[i + 1]));
		}
	}
	return (0);
}
