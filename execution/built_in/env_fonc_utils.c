#include "../../minishell.h"

void	insert_sorted_env(t_env **env, char *key, char *value)
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
	{
		// Aynı key varsa, değeri güncelle
		update_env(curr, value);
		return ;
	}
	// Yeni düğüm oluştur
	new = ft_malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = value ? ft_strdup(value) : NULL;
	new->next = curr;
	if (prev)
		prev->next = new;
	else
		*env = new;
}
void	export_key_only(t_env **env, const char *key)
{
	if (find_env(*env, key))
		return ;
	insert_sorted_env(env, (char *)key, NULL);
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
			if (prev) // ortadaysa ya da sondaysa
				prev->next = curr->next;
			else // head ise
				*env = curr->next;
			// free(curr->key);
			// free(curr->value);
			// free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
