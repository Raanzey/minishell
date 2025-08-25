/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:11:57 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:57 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_parser_error(char **tokens, int i)
{
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
		{
			if (i == 0 || !tokens[i + 1] || !ft_strncmp(tokens[i + 1], "|", 2))
				return (err_noext(ERR_SNTX, "`|'", 0, 2));
		}
		else if (is_redir(tokens[i]))
		{
			if (!tokens[i + 1])
				return (err_noext(ERR_SNTX, "`newline'", 0, 2));
			if (is_redir(tokens[i + 1]) || !ft_strncmp(tokens[i + 1], "|", 2))
				return (err_noext(ft_strjoin(ERR_SNTX, "`"),
						ft_strjoin(tokens[i + 1], "'"), 0, 2));
		}
	}
	return (0);
}
