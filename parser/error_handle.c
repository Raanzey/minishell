/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/03 12:00:13 by musisman          #+#    #+#             */
/*   Updated: 2025/06/03 12:00:13 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ambiguous_redirect_error(t_command *cmd)
{
	t_redirect *redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->filename && redir->filename[0] == '\0')
				return (err_prs("minishell: ", "ambiguous redirect", 2));
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	redir_error(t_command *cmd)
{
	t_redirect *redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (!redir->filename)
				return (err_prs(ERR_SNTX, "`|'", 2)); // değiştir doğrusunu yaz
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	handle_error(t_command *cmd)
{
	int exit_code;
	// if (redir_error(cmd))
	// 	return (1);

	exit_code = ambiguous_redirect_error(cmd);
	
	return (exit_code);
}

int	pre_parser_error(char **tokens, int i)
{
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
		{
			if (i == 0 || !tokens[i + 1] || !ft_strncmp(tokens[i + 1], "|", 2))
				return (err_prs(ERR_SNTX, "`|'", 2));
		}
		else if (!ft_strncmp(tokens[i], "<", 2)
			|| !ft_strncmp(tokens[i], ">", 2)
			|| !ft_strncmp(tokens[i], "<<", 3)
			|| !ft_strncmp(tokens[i], ">>", 3))
		{
			if (!tokens[i + 1])
				return (err_prs(ERR_SNTX, "`newline'", 2));
			if (!ft_strncmp(tokens[i + 1], "<", 2)
				|| !ft_strncmp(tokens[i + 1], ">", 2)
				|| !ft_strncmp(tokens[i + 1], "<<", 3)
				|| !ft_strncmp(tokens[i + 1], ">>", 3)
				|| !ft_strncmp(tokens[i + 1], "|", 2))
				return (err_prs(ERR_SNTX, tokens[i + 1], 2));
		}
	}
	return (0);
}
