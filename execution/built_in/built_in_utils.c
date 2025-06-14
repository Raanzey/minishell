# include "../../minishell.h"
//BURAYA ANA PROCESSDE ÇALIŞACAK BUİLT_İN FONKSİYONLARI GELECEK

int is_parent_builtin(t_command *cmd)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return 0;
	if (!ft_strncmp(cmd->av[0], "cd", 3)
		|| !ft_strncmp(cmd->av[0], "exit", 5)
		|| !ft_strncmp(cmd->av[0], "export", 7)
		|| !ft_strncmp(cmd->av[0], "unset", 6))
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

int export_cmd(char **av, t_env *env)
{
	int i = 1;
	char *eq;

	if (!av[i]) // sadece export → listeyi yazdır
	{
		print_export(env); // declare -x key="val"
		return 0;
	}
	while (av[i])
	{
		eq = ft_strchr(av[i], '=');
		if (eq) // KEY=VALUE varsa
			add_or_update_env(env, eq,av[i]);
		else // sadece KEY varsa, boş değerli ekle
			export_key_only(env, av[i]);
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
		else if (env->value != NULL) // boş değer
			printf("declare -x %s=\"\"\n", env->key);
		else // hiç değer yok
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}