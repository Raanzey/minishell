/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:22:25 by musisman          #+#    #+#             */
/*   Updated: 2025/07/23 17:22:25 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env	t_env;

typedef struct s_redirect
{
	int					type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**av;
	t_redirect			*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_expand
{
	t_env	*env_list;
	int		exit_code;
	int		first;
}	t_expand;

#endif
