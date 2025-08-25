/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:06:45 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:58:09 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	built_in(t_command *cmd, t_env **env_list, int exit_code)
{
	if (!ft_strncmp(cmd->av[0], "echo", 4) && cmd->av[0][4] == '\0')
		return (echo_cmd(cmd->av));
	else if (!ft_strncmp(cmd->av[0], "cd", 2) && cmd->av[0][2] == '\0')
		return (cd_cmd(cmd, env_list, NULL));
	else if (!ft_strncmp(cmd->av[0], "pwd", 3) && cmd->av[0][3] == '\0')
		return (pwd_cmd());
	else if (!ft_strncmp(cmd->av[0], "export", 6) && cmd->av[0][6] == '\0')
		return (export_cmd(cmd->av, env_list, cmd));
	else if (!ft_strncmp(cmd->av[0], "unset", 5) && cmd->av[0][5] == '\0')
		return (unset_cmd(cmd, env_list));
	else if (!ft_strncmp(cmd->av[0], "env", 3) && cmd->av[0][3] == '\0')
		return (env_cmd(*env_list));
	else if (!ft_strncmp(cmd->av[0], "exit", 4) && cmd->av[0][4] == '\0')
		return (exit_cmd(cmd->av, exit_code));
	else
		return (-1);
}

int	echo_cmd(char **str)
{
	int	i;
	int	n_flag;
	int	j;

	i = 0;
	n_flag = 0;
	while (str[++i] && !ft_strncmp(str[i], "-n", 2))
	{
		j = 2;
		while (str[i][j] == 'n')
			j++;
		if (str[i][j] != '\0')
			break ;
		n_flag = 1;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

int	env_cmd(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	pwd_cmd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		return (err_noext("pwd: ", 0, 1, 1));
	printf("%s\n", cwd);
	return (0);
}

int	exit_cmd(char **av, int exit_code)
{
	int	code;

	if (exit_code != -1)
		printf("exit\n");
	else
		exit_code = 0;
	if (!av[1])
		free_and_exit(exit_code);
	if (!is_numeric(av[1]))
		free_and_exit(err_noext("exit: ", ERR_EXIT, 0, 2));
	if (av[2])
		return (err_noext("exit: ", ERR_2_ARG, 0, 1));
	code = ft_atoi(av[1]) % 256;
	if (code < 0)
		code += 256;
	return (free_and_exit(code));
}
