/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:44:22 by musisman          #+#    #+#             */
/*   Updated: 2025/07/20 16:58:40 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // void	free_split(char **split)
// {
// 	int	i;

// 	if (!split)
// 		return ;
// 	i = 0;
// 	while (split[i])
// 	{
// 		// free(split[i]);
// 		i++;
// 	}
// 	// free(split);
// }

char	**clean_empty_args(char **av)
{
	int		i;
	int		j;
	int		start;
	char	**new;

	i = 0;
	j = 0;
	start = 0;
	if (!av)
		return (NULL);
	while (av[start] && (!av[start][0]))
		start++;
	while (av[start + j])
		j++;
	new = ft_calloc(j + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < j)
	{
		new[i] = ft_strdup(av[start + i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	clean_empty_args_inplace(t_command *cmd)
{
	t_command	*cur;
	char		**tmp;

	cur = cmd;
	while (cur)
	{
		tmp = clean_empty_args(cur->av);
		// free_split(cur->av);
		cur->av = tmp;
		cur = cur->next;
	}
}
