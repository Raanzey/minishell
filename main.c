/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:26:55 by musisman          #+#    #+#             */
/*   Updated: 2025/07/26 18:31:59 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0; // 0: prompt, 1: exec, 2: heredoc

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == 0 || g_signal == 3) // readline prompt sırasında
	{
		//write(1, "bura\n", 5);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 3;
	}
	else if (g_signal == 1) // exec child süreci
	{
		// write(1, "bura\n", 5);
		write(1, "\n", 1);
		ft_free(); // malloclı şeyler varsa
		exit(130);
	}
	else if (g_signal == 2) // heredoc sırasında
	{
		
		write(1, "\n", 1);
		ft_free();            // varsa tüm leak temizliği
		exit(130); 
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	discard_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_command	*cmd;
	t_env		*env_list;
	char **tokens;
	int exit_code;

	exit_code = 0;
	//signal(SIGINT, sigint_handler);
	env_list = init_env(env, 0);
	(void)av;
	if (ac >= 2)
		return (err_exp(ERR_ARG, 0, 0, 1));
	while (1)
	{
		g_signal = 0;
		
		setup_signals();

		// input = readline("minishell~ ");
		
		//* tester için eklendi
		//*----------------------------------------------
		if (isatty(fileno(stdin)))
			input = readline("minishell~ ");
		else
		{
			char *line = get_next_line(fileno(stdin));
			
				input = ft_strtrim(line, "\n");
				free(line);
			
		}
		//*----------------------------------------------
		
		// input = readline("minishell~ ");
		signal(SIGINT, sigint_handler);
		if (g_signal == 3)
		{
			exit_code = 130;
			g_signal = 0; // tekrar kullanıma hazırla
			// continue;
		}
		if (!input)
		{
    			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		tokens = tokenizer(input);
		if (!tokens || pre_parser_error(tokens, -1))
		{
			exit_code = 2;
			continue;
		}
		cmd = parser(tokens);
		if (!cmd)
		{
			continue;
		}
		expand_args(cmd, env_list, exit_code);
		if (handle_error(cmd))
		{
			exit_code = 2;
			continue;
		}
		clean_empty_args_inplace(cmd);
		exit_code = exec(cmd, &env_list);
	}
	ft_free();
	return (exit_code);
}

	