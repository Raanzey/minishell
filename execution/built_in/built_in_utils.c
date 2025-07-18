# include "../../minishell.h"

//BURAYA ANA PROCESSDE ÇALIŞACAK BUİLT_İN FONKSİYONLARI GELECEK

int is_parent_builtin(t_command *cmd)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return 0;
if ((!ft_strncmp(cmd->av[0], "cd", 2) && cmd->av[0][2] == '\0')
		|| (!ft_strncmp(cmd->av[0], "exit", 4) && cmd->av[0][4] == '\0')
		|| (!ft_strncmp(cmd->av[0], "export", 6) && cmd->av[0][6] == '\0')
		|| (!ft_strncmp(cmd->av[0], "unset", 5) && cmd->av[0][5] == '\0'))
		return 1;
	return 0;
}
int cd_cmd(char *str)
{
	char *path;
	if (!str)
	{
		path = getenv("HOME");
		if (!path)
			return 1;//PATH YOKSA HATA DURUMU
	}
	else
		path = str;
	if(chdir(path))
		printf("HATA\n");//error kullanılacak
	return 0;
}

int export_cmd(char **av, t_env **env)
{
	int i = 1;
	char *value;

	if (!av[i])
	{
		print_export(*env);
		return 0;
	}
	while (av[i])
	{
		value = ft_strchr(av[i], '=');
		if (value)
			add_or_update_env(env, value, av[i]);  // **env → env**
		else
			export_key_only(env, av[i]);
		i++;
	}
	return 0;
}
int unset_cmd(t_command *cmd,t_env **env_list)
{
	
	int i = 1;

	while (cmd->av[i])
	{
		unset_var(env_list ,cmd->av[i]); // global env list'ten sil
		i++;
	}
	return 0;
}
void print_export(t_env *env)
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