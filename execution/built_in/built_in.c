# include "../../minishell.h"

int built_in(t_command *cmd)
{
	if(!ft_strncmp(cmd->av[0], "echo",ft_strlen(cmd->av[0])))
		return (echo_cmd(cmd->av));
	else if(!ft_strncmp(cmd->av[0], "cd",ft_strlen(cmd->av[0]))) 
		return (cd_cmd(cmd->av[1]));
	else if(!ft_strncmp(cmd->av[0], "pwd",ft_strlen(cmd->av[0])))
		return (pwd_cmd(cmd->av[0]));
	else if(!ft_strncmp(cmd->av[0], "export",ft_strlen(cmd->av[0])))
		return 0;
	else if(!ft_strncmp(cmd->av[0], "unset",ft_strlen(cmd->av[0])))
		return 0;
	if(!ft_strncmp(cmd->av[0], "env",ft_strlen(cmd->av[0]))) 
		return 0;
	//EXIT GELCEKMİ ??????
	else
		return 1;//komut yok 
}


int echo_cmd(char **str)
{
	int i;
	i = 0;
	if (!ft_strncmp(str[1], "-n", ft_strlen(str[1])) && !(i++))//25 satır -n için -->!(i++)
	{
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

int cd_cmd(char *str)
{
	char cwd[1024];

    getcwd(cwd, sizeof(cwd));
	if(chdir(str))
		printf("HATA\n");//error kullanılacak
	getcwd(cwd, sizeof(cwd));
	printf("Sonra: %s\n", cwd);
	return 0;
}

int pwd_cmd(char *str)
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