#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Libft/libft.h"

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
int built_in(char **cmd)
{
	if(!ft_strncmp(cmd[1], "echo",ft_strlen(cmd[1])))
		return (0);
	else if(!ft_strncmp(cmd[1], "cd",ft_strlen(cmd[0]))) 
		return (cd_cmd(cmd[2]));
	else if(!ft_strncmp(cmd[1], "pwd",ft_strlen(cmd[0])))
		return 0;
	else if(!ft_strncmp(cmd[1], "export",ft_strlen(cmd[0])))
		return 0;
	else if(!ft_strncmp(cmd[0], "unset",ft_strlen(cmd[0])))
		return 0;
	if(!ft_strncmp(cmd[0], "env",ft_strlen(cmd[0]))) 
		return 0;
	//EXIT GELCEKMİ ??????
	else
		return 1;//komut yok 
}

int main(int argc, char **argv)
{
	if (built_in(argv))
		//hata durumu exit gelcek
	return 0;
}
