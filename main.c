
#include "minishell.h"

int exit_time(char *input)
{
	int returnnumber;
	char *tmp;

	returnnumber = 0;
	if (input[4])
	{
		tmp = ft_substr(input, 5, ft_strlen(input) - 5);
		returnnumber = ft_atoi(tmp);
		returnnumber = returnnumber % 256;
	}
	return (returnnumber);
}

int main(int ac, char **av)
{
	char *input;
	char *tmp1;
	char *tmp2;
	char *name;
	
	if (ac != 1)
		error(ERR_ARG);
	tmp1 = ft_substr(av[0], 2, 9);
	tmp2 = ft_strjoin(tmp1, "~ ");
	name = ft_strdup(tmp2);
	while (1)
	{
		input = readline(name);
		add_history(input);
		if (!ft_strncmp(input, "exit", 4) && (input[4] == 32 || !input[4]))
			return (exit_time(input));
		// parser();
	}
	free(input);
	free(tmp1);
	free(tmp2);
	free(name);
	return (0);
}
