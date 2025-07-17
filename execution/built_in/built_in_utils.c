#include "../../minishell.h"

// BURAYA ANA PROCESSDE ÇALIŞACAK BUİLT_İN FONKSİYONLARI GELECEK

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
int	cd_cmd(t_command *cmd)
{
	char	*path;

	if (!cmd->av[1] || !cmd->av[1][0])
	{
		path = getenv("HOME");
		if (!path)
			error("minishell: cd: `", cmd->av[1], ERR_CD, 2);
	}
	else if (cmd->av[2])
		error("minishell: cd: `", cmd->av[1], ERR_2_ARG, 1);
	else
		path = cmd->av[1];
	if (chdir(path))
		error("minishell: cd: `", 0, ERR_CD, 1);
	return (0);
}
//* Yeni eklendi export hata durumu için
int is_valid_identifier(char *str)
{
	int i = 0;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
//*

// int	export_cmd(char **av, t_env **env)
// {
// 	int		i;
// 	char	*value;

// 	i = 1;
// 	if (!av[i])
// 	{
// 		print_export(*env);
// 		return (0);
// 	}
// 	while (av[i])
// 	{
// 		value = ft_strchr(av[i], '=');
// 		if (value)
// 			add_or_update_env(env, value, av[i]); // **env → env**
// 		else
// 			export_key_only(env, av[i]);
// 		i++;
// 	}
// 	return (0);
// }

int	export_cmd(char **av, t_env **env)
{
	int		i;
	char	*value;

	i = 1;
	if (!av[i])
	{
		print_export(*env);
		return (0);
	}
	while (av[i])
	{
		if (!is_valid_identifier(av[i]))
			error("minishell: export: `", av[i], ERR_EXP, 1);
		value = ft_strchr(av[i], '=');
		if (value)
			add_or_update_env(env, value, av[i]);
		else
			export_key_only(env, av[i]);
		i++;
	}
	return (0);
}

int	unset_cmd(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->av[i])
	{
		unset_var(env_list, cmd->av[i]); // global env list'ten sil
		i++;
	}
	return (0);
}
void	print_export(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->value == NULL)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}