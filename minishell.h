/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:15 by musisman          #+#    #+#             */
/*   Updated: 2025/07/17 20:03:53 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
#include <sys/stat.h> // yeni eklendi exec_child için

# include "Libft/libft.h"
# include "parser/pars.h"
# include "execution/exec.h"

# define ERR_ARG "Please no argument\n"
# define ERR_EXIT ": numeric argument required\n"
# define ERR_2_ARG ": too many arguments\n"
# define ERR_CMD ": command not found\n"
# define ERR_CD ": No such file or directory\n"
# define ERR_EXP "': not a valid identifier\n"

extern int g_signal;

int	error(char *word, char *cmd, char *err, int exit_code);

#	endif