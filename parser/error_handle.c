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

int	ambiguous_redirect_error(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if ((!ft_strncmp(tokens[i], "<", 2)
			|| !ft_strncmp(tokens[i], ">", 2)
			|| !ft_strncmp(tokens[i], "<<", 3)
			|| !ft_strncmp(tokens[i], ">>", 3))
			&& (!tokens[i + 1] || tokens[i + 1][0] == '\0'))
		{
			printf("%s: ambiguous redirect\n", tokens[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	pipe_error(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
		{
			if (i == 0 || !tokens[i + 1] || !ft_strncmp(tokens[i + 1], "|", 2))
				return (print_unexpected_token("|"));
		}
		i++;
	}
	return (0);
}

int	redir_error(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "<", 2)
			|| !ft_strncmp(tokens[i], ">", 2)
			|| !ft_strncmp(tokens[i], "<<", 3)
			|| !ft_strncmp(tokens[i], ">>", 3))
		{
			if (!tokens[i + 1] || !ft_strncmp(tokens[i + 1], "<", 2)
					|| !ft_strncmp(tokens[i + 1], ">", 2)
					|| !ft_strncmp(tokens[i + 1], "<<", 3)
					|| !ft_strncmp(tokens[i + 1], ">>", 3)
					|| !ft_strncmp(tokens[i + 1], "|", 2)
					|| tokens[i + 1][0] == '\0')
				return (print_unexpected_token(tokens[i + 1]));
		}
		i++;
	}
	return (0);
}

int	handle_error(char **tokens)
{
	if (pipe_error(tokens))
		return (1);
	if (redir_error(tokens))
		return (1);
	if (ambiguous_redirect_error(tokens))
		return (1);
	return (0);
}

