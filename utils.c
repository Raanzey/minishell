/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:47 by musisman          #+#    #+#             */
/*   Updated: 2025/07/20 16:50:05 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *word, char *cmd, char *err, int exit_code)
{
	if (word)
		write(2, word, ft_strlen(word));
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, err, ft_strlen(err));
	ft_free();
	exit(exit_code);
}

int	err_prs(char *cmd, char *err, int exit_code)
{
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, err, ft_strlen(err));
	write(2, "\n", 2);
	return (exit_code);
}
