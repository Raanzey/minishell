/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:26:55 by musisman          #+#    #+#             */
/*   Updated: 2025/07/26 20:40:01 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == 0 || g_signal == 3)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 3;
	}
	else if (g_signal == 1)
	{
		write(1, "\n", 1);
		ft_free();
		exit(130);
	}
	else if (g_signal == 2)
	{
		write(1, "\n", 1);
		ft_free();
		exit(130);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	discard_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

t_command	*do_parser(char *in, int *exit_code, t_env *env_list)
{
	t_command	*cmd;
	char		**tokens;

	tokens = tokenizer(in);
	if (!tokens || pre_parser_error(tokens, -1))
	{
		*exit_code = 2;
		return (0);
	}
	cmd = parser(tokens);
	if (!cmd)
		return (0);
	expand_args(cmd, env_list, *exit_code);
	if (handle_error(cmd))
	{
		*exit_code = 2;
		return (0);
	}
	clean_empty_args_inplace(cmd);
	if (!cmd->redir)
	{
		if (!cmd->av || !cmd->av[0])
			return (0);
	}
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*in;
	t_env	*env_list;
	int		exit_code;

	exit_code = 0;
	env_list = init_env(env, 0);
	(void)av;
	if (ac >= 2)
		return (err_exp(ERR_ARG, 0, 0, 1));
	while (1)
	{
		g_signal = 0;
		setup_signals();
		in = readline("minishell~ ");
		signal(SIGINT, sigint_handler);
		if (g_signal == 3)
		{
			exit_code = 130;
			g_signal = 0;
		}
		if (!in)
		{
			printf("exit\n");
			break ;
		}
		if (*in)
			add_history(in);
		// if (!do_parser(in, &exit_code, env_list))
		// 	continue;
		exit_code = exec(do_parser(in, &exit_code, env_list), &env_list);
	}
	ft_free();
	return (exit_code);
}
