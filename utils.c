/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:47 by musisman          #+#    #+#             */
/*   Updated: 2025/07/22 19:11:14 by yozlu            ###   ########.fr       */
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

int	err_built_in(t_command *cmd, char *av, char *err_message ,int exit_code)
{
	write(2, "minishell: ", 11);
	if (is_parent_builtin(cmd))
	{
		write(2, cmd->av[0], ft_strlen(cmd->av[0]));
		if (ft_strcmp(err_message, ERR_2_ARG))
		{
			if (!av)
				write(2, ": ", 3);
			else if (av)
			{
				write(2, ": `", 3);
				write(2, av, ft_strlen(av));
			}
		}
		write(2, err_message, ft_strlen(err_message));
	}
	return exit_code;
}
