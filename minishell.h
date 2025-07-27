/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:15 by musisman          #+#    #+#             */
/*   Updated: 2025/07/27 15:17:03 by yozlu            ###   ########.fr       */
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
# include <sys/stat.h>

# include "Libft/libft.h"
# include "collector/collector.h"
# include "parser/pars.h"
# include "execution/exec.h"

# define EXP  "export: `"

# define ERR_ARG "Please no argument"
# define ERR_EXIT "numeric argument required"
# define ERR_2_ARG "too many arguments"
# define ERR_CMD ": command not found"
# define ERR_CD ": No such file or directory"
# define ERR_HOME "HOME not set"
# define ERR_EXP "': not a valid identifier"
# define ERR_SNTX "syntax error near unexpected token "
# define ERR_PRM ": Permission denied"
# define ERR_DIC ": Is a directory"

extern int	g_signal;

int	error(char *word, char *cmd, char *err, int exit_code);
int	err_exp(char *cmd, char *file, int err, int exit_code);
void	sigint_handler(int sig);

#endif