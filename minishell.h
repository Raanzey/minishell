/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:27:15 by musisman          #+#    #+#             */
/*   Updated: 2025/07/15 20:02:47 by yozlu            ###   ########.fr       */
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

# include "Libft/libft.h"
# include "parser/pars.h"
# include "execution/exec.h"

# define ERR_ARG "Please no argument\n" // .minishell dasda hata durumu
# define ERR_EXIT "numeric argument required\n" // exit dsda hata durumu

extern int g_signal;

int	error(char *err);

#	endif