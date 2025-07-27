/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:09:50 by musisman          #+#    #+#             */
/*   Updated: 2025/07/27 16:58:15 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->value == NULL)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*find_path(char *cmd, t_env *env_list)
{
	char	**paths;
	char	*tmp;
	char	*candidate;
	char	*full_path;
	int		i;

	i = 0;
	tmp = ft_path(env_list);
	if (!tmp)
		error("minishell: ", cmd, ERR_CD, 127);
	paths = ft_split(tmp, ':');
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(candidate, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	**convert_env_to_array(t_env *env, int count, int i, char *joined)
{
	t_env	*tmp;
	char	**env_array;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	env_array = ft_malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			joined = ft_strjoin(tmp->key, "=");
			env_array[i++] = ft_strjoin(joined, tmp->value);
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
