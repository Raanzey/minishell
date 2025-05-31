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