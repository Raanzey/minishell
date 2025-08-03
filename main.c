/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:26:55 by musisman          #+#    #+#             */
/*   Updated: 2025/08/03 12:57:33 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

static void	signals_and_input(char **in, int *exit_code)
{
	*in = readline("minishell~ ");
	signal(SIGINT, sigint_handler);
	if (g_signal == 3)
	{
		*exit_code = 130;
		g_signal = 0;
	}
}

static int	check_input(char *in)
{
	if (!in)
	{
		printf("exit\n");
		return (0);
	}
	if (*in)
		add_history(in);
	return (1);
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
	if (!expand_args(cmd, env_list, *exit_code))
	{
		*exit_code = 1;
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

t_status	*init_stat(int prev_fd, int heredoc_status, int code)
{
	t_status	*status;

	status = ft_malloc(sizeof(t_status));
	status->prev_fd = prev_fd;
	status->heredoc_status = heredoc_status;
	status->exit_code = code;
	return (status);
}

int	main(int ac, char **av, char **env)
{
	char		*in;
	t_env		*env_list;
	t_command	*cmd;
	t_status	*status;
	int			exit_code;

	exit_code = 0;
	(void)av;
	if (ac >= 2)
		return (err_noext(ERR_ARG, 0, 0, 1));
	env_list = init_env(env, 0);
	while (1)
	{
		g_signal = 0;
		setup_signals();
		signals_and_input(&in, &exit_code);
		if (!check_input(in))
			break ;
		cmd = do_parser(in, &exit_code, env_list);
		status = init_stat(-1, 0, exit_code);
		if (cmd)
			exit_code = exec(cmd, &env_list, status);
	}
	ft_free();
	return (exit_code);
}
