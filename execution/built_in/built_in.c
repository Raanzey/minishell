# include "../../minishell.h"

int built_in(t_command *cmd)
{
	if(!ft_strncmp(cmd->av[0], "echo",ft_strlen(cmd->av[0])))
		return (echo_cmd(cmd->av));
	else if(!ft_strncmp(cmd->av[0], "cd",ft_strlen(cmd->av[0]))) 
		return 0;
	else if(!ft_strncmp(cmd->av[0], "pwd",ft_strlen(cmd->av[0])))
		return 0;
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
	i = 1;
	if (!ft_strncmp(str[2], "-n", ft_strlen(str[2])) && !(i++))
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



