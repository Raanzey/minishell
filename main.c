/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:26:55 by musisman          #+#    #+#             */
/*   Updated: 2025/07/03 06:24:18 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO exit dsadas ahta durumunu işlemeye çalıştım ama yapamadım 
//TODO eğer "exit dsadas" girersem 2 döndürüyor ve çıktı olarak bash: exit: dsadas: numeric argument required verip çıkıyor
//TODO "exit 3213 32132" ya da "exit 3213 dsadas" girersem too many arguments diyor ve 1 döndürüyor ama çıkmıyor
//TODO ayrıca exit built-in fonksiyonmuş bununla boşuna uğraşmışm :(

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
	free(input);
	return (returnnumber);
}

int  g_exit_code = 999;

int	main(int ac, char **av)
{
	char		*input;
	t_command	*cmd;
	char **tokens;
	char  **expand;

	(void)av;
	if (ac >= 2)
		return (1); //? error(ERR_ARG) neden saçmalıyor
	while (1)
	{
		input = readline("minishell~ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!ft_strncmp(input, "exit", 4) && (input[4] == ' ' || !input[4]))
		{
			// free(input);
			return (exit_time(input)); //* varsayılan olarak sadece çık
		}
		tokens = tokenizer(input);
		int q = -1;
		printf("\nTOKENIZER\n\n"); //* token yazdırma
		if (!tokens)
		{	
			printf("Token failed.\n");
			free_tokens(tokens);
			free(input);
			continue;
		}
		else
		{
			while (tokens[++q])
				printf("token[%d]: %s\n", q, tokens[q]);
		}
		expand = expand_args(tokens,g_exit_code);
		q = -1;
		printf("\nEXPANSION\n\n"); //* token yazdırma
		if (!expand || handle_error(expand))
		{
			printf("Expand failed.\n");
			// free_tokens(tokens); //? ||| durumunda abort alıyor neden
			// if (expand)
				// free_tokens(expand); // burada tüm tokenları temizle
			free(input);
			continue;
		}
		else
		{
			while (expand[++q])
				printf("token[%d]: %s\n", q, expand[q]);
		}
		
		printf("\nPARSER\n\n");
		cmd = parser(expand);
		if (!cmd)
		{
			printf("Parsing failed.\n");
			free_tokens(tokens);
			free_tokens(expand);
			free(input);
			continue;
		}
		print_cmd(cmd); //* parser yazdırma

		// exec(cmd); 
		// iki error olacak biri return edecek biri main içinde kontrol edip continue edecek
		free_command(cmd);
		free_tokens(tokens);
		free_tokens(expand);
		free(input);
	}
	return (0);
}

