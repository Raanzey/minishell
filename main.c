#include "minishell.h"

//TODO exit dsadas ahta durumunu işlemeye çalıştım ama yapamadım 
//TODO eğer "exit dsadas" girersem 2 döndürüyor ve çıktı olarak bash: exit: dsadas: numeric argument required verip çıkıyor
//TODO "exit 3213 32132" ya da "exit 3213 dsadas" girersem too many arguments diyor ve 1 döndürüyor ama çıkmıyor
//TODO ayrıca exit built-in fonksiyonmuş bununla boşuna uğraşmışm :(

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

int	main(int ac, char **av)
{
	char		*input;
	t_command	*cmd;
	char **tokens;

	(void)av;
	if (ac >= 2)
		return (error(ERR_ARG));
	while (1)
	{
		input = readline("minishell~ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!ft_strncmp(input, "exit", 4) && (input[4] == ' ' || !input[4]))
		{
			free(input);
			return (exit_time(input)); //* varsayılan olarak sadece çık
		}
		tokens = tokenizer(input);
		if (!tokens)
		{
			printf("Token failed.\n");
			free(input);
			continue;
		}

		cmd = parser(tokens);
		if (!cmd)
		{
			printf("Parsing failed.\n");
			free(input);
			continue;
		}
		print_cmd(cmd);
		//TODO cmd freelemeyi unutma
		free(input);
	}
	return (0);
}

