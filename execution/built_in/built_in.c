# include "../../minishell.h"

int built_in(t_command *cmd, t_env **env_list)
{
	if(!ft_strncmp(cmd->av[0], "echo", 4) && cmd->av[0][4] == '\0')
		return (echo_cmd(cmd->av));
	else if(!ft_strncmp(cmd->av[0], "cd", 2) && cmd->av[0][2] == '\0') 
		return (cd_cmd(cmd));
	else if(!ft_strncmp(cmd->av[0], "pwd", 3) && cmd->av[0][3] == '\0')
		return (pwd_cmd());
	// else if(!ft_strncmp(cmd->av[0], "export", 6) && cmd->av[0][6] == '\0')
	// 	return (export_cmd(cmd->av, env_list, cmd));
	else if(!ft_strncmp(cmd->av[0], "export", 6) && cmd->av[0][6] == '\0')
		return (export_cmd(cmd->av, env_list));
	else if(!ft_strncmp(cmd->av[0], "unset", 5) && cmd->av[0][5] == '\0')
		return (unset_cmd(cmd, env_list));
	else if(!ft_strncmp(cmd->av[0], "env", 3) && cmd->av[0][3] == '\0') 
		return (env_cmd(*env_list));
	else if (!ft_strncmp(cmd->av[0], "exit", 4) && cmd->av[0][4] == '\0')
		return (exit_cmd(cmd->av));
	else
		return -1;//komut yok 
}
int echo_cmd(char **str)
{
	int i;
	
	i = 0;
	if (str[1] && !ft_strncmp(str[1], "-n", ft_strlen(str[1])) && !(i++))//25 satır -n için -->!(i++)
	{//!echo -nnnnnnnnnnn merhaba yazması lazım echo -nnnnnnnnn -n -nnnnnnnnn merhaba yazması lazım yazmıyor
		while (str[++i])
		{
			if (!str[i + 1])
				printf("%s", str[i]);
			else
				printf("%s ", str[i]);
		}
	}
	else
	{
		while (str[++i])
		{
			if (!str[i + 1])
				printf("%s", str[i]);
			else
				printf("%s ", str[i]);
		}
		printf("\n");
	}
	return 0;
}
int env_cmd(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return 0;
}


int pwd_cmd()
{
	char cwd[1024];
    if(!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");//hata DURUMUUUUU    
		return 1;
	}	
	printf("%s\n", cwd);
	return 0;
}

int	exit_cmd(char **av)
{
	int code;

	printf("exit\n");
	if (!av[1])
	{
		ft_free();
		exit(0);
	}
	if (!is_numeric(av[1]))
		error("minishell: exit: `", 0, ERR_EXIT, 2);
	if (av[2])
		error("minishell: exit: `", 0, ERR_2_ARG, 1);
	code = ft_atoi(av[1]) % 256;
	if (code < 0)
		code += 256;
	ft_free();
	exit(code);
}
