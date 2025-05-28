#include "../minishell.h"

static int	creat_process(char **av, char **env, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		if (built_in(cmd))
		{
			/* code */
		}
		
	return (pid);
}

int exec(t_command *cmd)
{
	t_command *tmp;
	int pid = 0;
	tmp = cmd;
    while(tmp->next)
    {
        pid = creat_process(cmd->av);
        waitpid(pid);
        tmp = tmp->next;
    }
	if (built_in(cmd))
	{
		return 0;
		printf("HATA\n");//error kullanılacak
	}
	return 0;
}