/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:47 by musisman          #+#    #+#             */
/*   Updated: 2025/07/27 17:01:09 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *word, char *cmd, char *err, int exit_code)
{
	char *msg;
	
	msg = "\0";
	if (word)
		msg = ft_strjoin(msg, "minishell: ");
	if (cmd)
		msg = ft_strjoin(msg, cmd);
	if (err)
		msg = ft_strjoin(msg, err);
	ft_strjoin(msg, "\n");
	write(2, msg, ft_strlen(msg));
	ft_free();
	exit(exit_code);
}

int	err_exp(char *cmd, char *file, int bool_err, int exit_code)
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
		msg = ft_strjoin(msg, "\n");
		write(2, msg, ft_strlen(msg));
	}
	return (exit_code);
}
