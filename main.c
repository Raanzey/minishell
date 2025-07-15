/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:26:55 by musisman          #+#    #+#             */
/*   Updated: 2025/07/15 19:15:32 by musisman         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	char		*input;
	t_command	*cmd;
	char **tokens;

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
			int q = -1;
			while (tokens[++q])
				printf("token[%d]: %s\n", q, tokens[q]);
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

		expand_args(cmd, cmd->exit_code);
		// printf("\ndeneme\n");
		// 	print_cmd(cmd); //* expansion yazdırma
		// printf("\ndeneme\n");

		if (handle_error(cmd))
		{
			free_command(cmd);
			free_tokens(tokens);
			free(input);
			continue;
		}
		else
		{
			printf("\nEXPANSION\n\n");
			print_cmd(cmd); //* expansion yazdırma
		}

		// exec(cmd); 
		// iki error olacak biri return edecek biri main içinde kontrol edip continue edecek
		free_command(cmd);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}

// < "$EMPTY" //TODOfarklı çalışıyor düzelt

// ** minishell **
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler/3.2__Minishell/minishell (0) $ ./minishell
// 	minishell~ < "$EMPTY"
	
// 	TOKENIZER
	
// 	token[0]: <
// 	token[1]: "$EMPTY"
	
// 	EXPANSION
	
// 	syntax error near unexpected token `newline'
// 	Expand failed.
// 	minishell~ 

// ** bash **
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (0) $ < "$EMPTY"
// 	-bash: : No such file or directory
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ < bla
// 	-bash: bla: No such file or directory
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ 


// < $EMPTY

// ** minishell **
// 	minishell~ < $EMPTY
	
// 	TOKENIZER
	
// 	token[0]: <
// 	token[1]: $EMPTY
	
// 	EXPANSION
	
// 	syntax error near unexpected token `newline'
// 	Expand failed.
// 	minishell~
// ** bash **
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ < $EMPTY   
// 	-bash: $EMPTY: ambiguous redirect
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ 



// echo a > "$EMPTY"

// ** minishell **
// 	minishell~ echo a > "$EMPTY"
	
// 	TOKENIZER
	
// 	token[0]: echo
// 	token[1]: a
// 	token[2]: >
// 	token[3]: "$EMPTY"
	
// 	EXPANSION
	
// 	syntax error near unexpected token `newline'
// 	Expand failed.
// 	minishell~ 

// ** bash **
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ echo a > "$EMPTY"
// 	-bash: : No such file or directory
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ 



// echo a > $EMPTY

// ** minishell **
// 	minishell~ echo a > $EMPTY
	
// 	TOKENIZER
	
// 	token[0]: echo
// 	token[1]: a
// 	token[2]: >
// 	token[3]: $EMPTY
	
// 	EXPANSION
	
// 	syntax error near unexpected token `newline'
// 	Expand failed.
// 	minishell~

// ** bash **
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ echo a > $EMPTY
// 	-bash: $EMPTY: ambiguous redirect
// 	mershim@ErsinAsmEslem:/mnt/c/Users/musta/OneDrive/Masaüstü/42 projeler (1) $ 
	