/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:12:55 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:12:55 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*add_command(char **tokens, size_t *i)
{
	t_command	*cmd;
	t_redirect	*r;

	cmd = new_command();
	while (tokens[*i] && ft_strncmp(tokens[*i], "|", 2))
	{
		if (is_redir(tokens[*i]))
		{
			if (!tokens[*i + 1])
				return (NULL);
			r = new_redirect(tokens[*i], tokens[*i + 1]);
			add_redirect(cmd, r);
			*i += 2;
		}
		else
			add_arg(cmd, tokens[(*i)++]);
	}
	return (cmd);
}

t_command	*parser(char **tokens)
{
	t_command	*first;
	t_command	*cur;
	t_command	*cmd;
	size_t		i;

	first = NULL;
	cur = NULL;
	i = 0;
	while (tokens[i])
	{
		cmd = add_command(tokens, &i);
		if (!cmd)
			return (NULL);
		if (!first)
			first = cmd;
		else
			cur->next = cmd;
		cur = cmd;
		if (tokens[i] && !ft_strncmp(tokens[i], "|", 2))
			i++;
	}
	return (first);
}
