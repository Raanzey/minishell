/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:22:46 by musisman          #+#    #+#             */
/*   Updated: 2025/07/28 16:35:07 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = ft_malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(char *s)
{
	return (!ft_strncmp(s, "<", 2) || !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3) || !ft_strncmp(s, ">>", 3));
}

t_redirect	*create_redirect(char *op, char *file)
{
	t_redirect	*r;

	r = ft_malloc(sizeof(t_redirect));
	if (!r || !file)
		return (NULL);
	r->filename = ft_strdup(file);
	r->next = NULL;
	if (!ft_strncmp(op, "<<", 3))
		r->type = 4;
	else if (!ft_strncmp(op, ">>", 3))
		r->type = 2;
	else if (!ft_strncmp(op, "<", 2))
		r->type = 3;
	else if (!ft_strncmp(op, ">", 2))
		r->type = 1;
	return (r);
}

void	add_redirect(t_command *cmd, t_redirect *r)
{
	t_redirect	*cur;

	cur = cmd->redir;
	if (!cur)
		cmd->redir = r;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = r;
	}
}

void	add_arg(t_command *cmd, char *word)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = -1;
	while (cmd->av && cmd->av[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	while (++j < i)
		new[j] = cmd->av[j];
	new[i] = ft_strdup(word);
	new[i + 1] = NULL;
	cmd->av = new;
}
