/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:07:31 by musisman          #+#    #+#             */
/*   Updated: 2025/07/29 14:49:48 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_parent_builtin(t_command *cmd)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return (0);
	if ((!ft_strncmp(cmd->av[0], "cd", 2) && cmd->av[0][2] == '\0')
		|| (!ft_strncmp(cmd->av[0], "exit", 4) && cmd->av[0][4] == '\0')
		|| (!ft_strncmp(cmd->av[0], "export", 6) && cmd->av[0][6] == '\0')
		|| (!ft_strncmp(cmd->av[0], "unset", 5) && cmd->av[0][5] == '\0'))
		return (1);
	return (0);
}

static char	*get_cd_target(t_command *cmd, t_env **env_list)
{
	char	*path;

	if (!cmd->av[1] || !ft_strcmp(cmd->av[1], "~"))
	{
		path = get_env_value(*env_list, "HOME");
		if (!path)
			return (err_exp("cd: ", ERR_HOME, 0, 1), NULL);
	}
	else if (!ft_strcmp(cmd->av[1], "-"))
	{
		path = get_env_value(*env_list, "OLDPWD");
		if (!path)
			return (err_exp("cd: ", "OLDPWD not set", 0, 1), NULL);
		printf("%s\n", path);
	}
	else
		path = cmd->av[1];
	return (path);
}

int	cd_cmd(t_command *cmd, t_env **env_list, char *path)
{
	char	old_cwd[1024];
	char	new_cwd[1024];

	if (cmd->av[1] && cmd->av[2])
		return (err_exp("cd: ", ERR_2_ARG, 0, 1));
	if (!getcwd(old_cwd, sizeof(old_cwd)))
		return (err_exp("cd: ", "getcwd failed", 0, 1));
	path = get_cd_target(cmd, env_list);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (err_exp("cd: ", path, 1, 1));
	insert_sorted_exp(env_list, "OLDPWD", old_cwd);
	if (getcwd(new_cwd, sizeof(new_cwd)))
		insert_sorted_exp(env_list, "PWD", new_cwd);
	return (0);
}

int	export_cmd(char **av, t_env **env, t_command *cmd)
{
	int		i;
	char	*value;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!av[i])
		return (print_export(*env), 0);
	while (av[i])
	{
		if (!is_valid_identifier(av[i]))
		{
			exit_code = err_exp(ft_strjoin(EXP, cmd->av[i++]), ERR_EXP, 0, 1);
			continue ;
		}
		value = ft_strchr(av[i], '=');
		if (value)
			add_or_update_env(env, value, av[i]);
		else
			export_key_only(env, av[i]);
		i++;
	}
	return (exit_code);
}

int	unset_cmd(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->av[i])
	{
		unset_var(env_list, cmd->av[i]);
		i++;
	}
	return (0);
}
