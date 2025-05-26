
#include "minishell.h"

// **  BETTER  COMMENTS eklentisi ile daha güzel comment satırları :D
//TODO exit dsadas ahta durumunu işlemeye çalıştım ama yapamadım 
//TODO eğer "exit dsadas" girersem 2 döndürüyor ve çıktı olarak bash: exit: dsadas: numeric argument required verip çıkıyor
//TODO "exit 3213 32132" ya da "exit 3213 dsadas" girersem too many arguments diyor ve 1 döndürüyor ama çıkmıyor
//TODO ayrıca exit built-in fonksiyonmuş bununla boşuna uğraşmışm :(

// int exit_time(char *input)
// {
// 	int returnnumber;
// 	char *tmp;
// 	int i;

// 	i = -1;
// 	returnnumber = 0;
// 	if (input[4])
// 	{
// 		tmp = ft_substr(input, 5, ft_strlen(input) - 5);
// 		printf("tmp: %s\n",tmp);
// 		returnnumber = ft_atoi(tmp);
// 		printf("1: %d\n",returnnumber);
// 		while (++i < (int)ft_strlen(tmp))
// 		{
// 			if (!ft_isdigit(tmp[i]))
// 			{
// 				returnnumber = 2;
// 				printf("minishell: exit: %s", tmp);
// 				error(ERR_EXIT);
// 				break;
// 			}
// 		}
// 		printf("2: %d\n",returnnumber);
// 		returnnumber = returnnumber % 256;
// 		printf("3: %d\n",returnnumber);
// 	}
// 	return (returnnumber);
// }

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
	
	(void)av;
	if (ac >= 2)
		return (error(ERR_ARG));
	while (1)
	{
		input = readline("minishell~ ");
		add_history(input);
		if (!ft_strncmp(input, "exit", 4) && (input[4] == 32 || !input[4]))
			return (exit_time(input));
		printf("buraa\n");
		exec(parser(input));
	}
	free(input);
	return (0);
}
