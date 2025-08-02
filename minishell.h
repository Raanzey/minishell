/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:15 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:57:40 by musisman         ###   ########.fr       */
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

# include "libmini/libmini.h"
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
# define ERR_OLDPWD "OLDPWD not set"
# define ERR_EXP "': not a valid identifier"
# define ERR_SNTX "syntax error near unexpected token "
# define ERR_RDR "ambiguous redirect"
# define ERR_QUOTE "syntax error near open quote "
# define ERR_PRM ": Permission denied"
# define ERR_DIC ": Is a directory"

extern int	g_signal;

int		free_and_exit(int exit_code);
int		err_ext(char *word, char *cmd, char *err, int exit_code);
int		err_noext(char *cmd, char *file, int bool_err, int exit_code);
void	sigint_handler(int sig);

#endif