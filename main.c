#include "minishell.h"

// TODO exit dsadas ahta durumunu işlemeye çalıştım ama yapamadım
// TODO eğer "exit dsadas" girersem 2 döndürüyor ve çıktı olarak bash: exit: dsadas: numeric argument required verip çıkıyor
// TODO "exit 3213 32132" ya da "exit 3213 dsadas" girersem too many arguments diyor ve 1 döndürüyor ama çıkmıyor
// TODO ayrıca exit built-in fonksiyonmuş bununla boşuna uğraşmışm :(

// t_env *g_env_list = NULL;
// volatile sig_atomic_t g_received_signal = 0;
int		g_signal;
void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal==0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal==1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
 	}
	else if (g_signal==2)
		close(STDIN_FILENO);
}

int	exit_time(char *input)
{
	int		returnnumber;
	char	*tmp;

	returnnumber = 0;
	if (input[4])
	{
		tmp = ft_substr(input, 5, ft_strlen(input) - 5);
		returnnumber = ft_atoi(tmp);
		returnnumber = returnnumber % 256;
	}
	return (returnnumber);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	char		**tokens;
	t_command	*cmd;
	t_env		*env_list;

	// int q;
	//setup_signals();
	signal(SIGINT, sigint_handler);
	env_list = init_env(env, 0);
	(void)av;
	if (ac >= 2)
		return (error(ERR_ARG));
	while (1)
	{
		g_signal = 0;
		input = readline("minishell~ ");
		signal(SIGINT, sigint_handler);
		if (!input)
		{
			write(1, "exit\n", 5); // shell gibi davran
			exit(0);
		}
		if (*input)
			add_history(input);
		if (!ft_strncmp(input, "exit", 4) && (input[4] == ' ' || !input[4]))
		{
			return (exit_time(input)); //* varsayılan olarak sadece çık
		}
		tokens = tokenizer(input);
		if (!tokens)
		{
			// printf("Token failed.\n");
			free(input);
			continue ;
		}
		cmd = parser(tokens);
		if (!cmd)
		{
			printf("Parsing failed.\n");
			free(input);
			continue ;
		}
		// print_cmd(cmd); //* parser yazdırma
		exec(cmd, &env_list);
		// TODO cmd freelemeyi unutma
		free(input);
	}
	return (0);
}
