/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:26:55 by musisman          #+#    #+#             */
/*   Updated: 2025/07/20 20:44:04 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(char **tokens)
{
	int i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->av)
		{
			i = -1;
			while (cmd->av[++i])
				free(cmd->av[i]);
			free(cmd->av);
		}
		free_redirects(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}


int		g_signal;

void	setup_signals_main()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
void	handle_sigint_exec(int sig)
{
	(void)sig;
	if (isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "\n", 1);
		//leak olur ft_free ekle amk.
	exit(130);
}

void	discard_signals()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

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
	// else if (g_signal==1)
	// {
	// 	// write(1, "\n", 1);
	// 	// rl_on_new_line();
 	// }
	else if (g_signal==2)
		close(STDIN_FILENO);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_command	*cmd;
	t_env		*env_list;
	char **tokens;
	int exit_code;

	exit_code = 0;
	signal(SIGINT, sigint_handler);
	env_list = init_env(env, 0);
	(void)av;
	if (ac >= 2)
		return (1); //? error(ERR_ARG) neden saçmalıyor
	while (1)
	{
		g_signal = 0;
		input = readline("minishell~ ");
		signal(SIGINT, sigint_handler);
		if (!input)
		{
			if (g_signal != 1)
				write(1, "exit", 5); // readline NULL ise yani Ctrl+D
			break;
		}
		if (*input)
			add_history(input);
		
		tokens = tokenizer(input);
		if (!tokens || pre_parser_error(tokens, -1))
		{	
			// printf("Token failed.\n");
			free_tokens(tokens);
			free(input);
			continue;
		}
		else
		{
			// printf("\nTOKENIZER\n\n"); //* token yazdırma
			// int q = -1;
			// while (tokens[++q])
			// 	printf("token[%d]: %s\n", q, tokens[q]);
		}

		cmd = parser(tokens);
		if (!cmd)
		{
			free_tokens(tokens);
			free(input);
			continue;
		}
		else
		{
			// printf("\nPARSER\n\n");
			// print_cmd(cmd); //* parser yazdırma
		}

		expand_args(cmd, exit_code);
		if (handle_error(cmd))
		{
			free_command(cmd);
			free_tokens(tokens);
			free(input);
			continue;
		}
		else
		{
			// printf("\nEXPANSION\n\n");
			// print_cmd(cmd); //* expansion yazdırma
		}
		clean_empty_args_inplace(cmd);
		// print_cmd(cmd); //* expansion yazdırma

		exit_code = exec(cmd, &env_list);
		// exec(cmd); 
		// iki error olacak biri return edecek biri main içinde kontrol edip continue edecek
		free_command(cmd);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}

	