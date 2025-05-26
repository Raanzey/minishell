#include "../minishell.h"
void exec(t_command *cmd)
{
	if (built_in(cmd))
	{
		return 0;
		//hata durumu exit gelcek
	}
	
}