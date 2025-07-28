/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:09:56 by musisman          #+#    #+#             */
/*   Updated: 2025/07/28 21:41:15 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	insert_sorted_exp(t_env **env, char *key, char *value)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*new;

	curr = *env;
	prev = NULL;
	while (curr && ft_strcmp(curr->key, key) < 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr && ft_strcmp(curr->key, key) == 0)
		return (update_env(curr, value));
	new = create_env_node(key, value, curr);
	if (!new)
		return ;
	if (prev)
		prev->next = new;
	else
		*env = new;
}

t_env	*init_env(char **env, int i)
{
	t_env	*env_list;
	char	*eq;
	int		key_len;
	char	*key;
	char	*val;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (!eq)
		{
			i++;
			continue ;
		}
		key_len = eq - env[i];
		key = ft_substr(env[i], 0, key_len);
		val = ft_strdup(eq + 1);
		insert_sorted_exp(&env_list, key, val);
		i++;
	}
	return (env_list);
}

void	update_env(t_env *node, const char *value)
{
	if (!node)
		return ;
	node->value = ft_strdup(value);
}

void	add_or_update_env(t_env **env, char *eq, char *av)
{
	int		key_len;
	char	*key;
	char	*val;

	key_len = eq - av;
	key = ft_substr(av, 0, key_len);
	val = ft_strdup(eq + 1);
	insert_sorted_exp(env, key, val);
}

void	export_key_only(t_env **env, const char *key)
{
	if (find_env(*env, key))
		return ;
	insert_sorted_exp(env, (char *)key, NULL);
}
