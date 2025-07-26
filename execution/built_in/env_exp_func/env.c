#include "../../../minishell.h"

t_env	*find_env(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, const char *key)
{
	if (!env->value)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	*ft_path(t_env *env)
{
	char	*path_env;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	return (ft_strdup(path_env));
}

void	unset_var(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key))
			&& curr->key[ft_strlen(key)] == '\0')
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_env	*create_env_node(char *key, char *value, t_env *next)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = next;
	return (new);
}
