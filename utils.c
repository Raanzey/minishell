/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:47 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:57:25 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_exit(int exit_code)
{
	ft_free();
	exit(exit_code);
}

int	err_ext(char *word, char *cmd, char *err, int exit_code)
{
	char	*msg;

	msg = "\0";
	if (word)
		msg = ft_strjoin(msg, word);
	if (cmd)
		msg = ft_strjoin(msg, cmd);
	if (err)
		msg = ft_strjoin(msg, err);
	write(2, msg, ft_strlen(msg));
	printf("\n");
	return (free_and_exit(exit_code));
}

int	err_noext(char *cmd, char *file, int bool_err, int exit_code)
{
	char	*msg;

	msg = "minishell: ";
	if (cmd)
		msg = ft_strjoin(msg, cmd);
	if (file)
		msg = ft_strjoin(msg, file);
	if (bool_err)
		perror(msg);
	else
	{
		write(2, msg, ft_strlen(msg));
		printf("\n");
	}
	return (exit_code);
}
