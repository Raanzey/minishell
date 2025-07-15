# include "../../minishell.h"
int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void insert_sorted_env(t_env **env, char *key, char *value)
{
	t_env *curr = *env;
	t_env *prev = NULL;

	
	while (curr && ft_strcmp(curr->key, key) < 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr && ft_strcmp(curr->key, key) == 0)
	{
		// Aynı key varsa, değeri güncelle
		update_env(curr, value);
		return;
	}

	// Yeni düğüm oluştur
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return;
	new->key = ft_strdup(key);
	new->value = value ? ft_strdup(value) : NULL;
	new->next = curr;

	if (prev)
		prev->next = new;
	else
		*env = new;
}
void export_key_only(t_env **env, const char *key)
{
	if (find_env(*env, key))
		return;

	insert_sorted_env(env, (char *)key, NULL);
}
void unset_var(t_env **env, const char *key)
{
	t_env *curr = *env;
	t_env *prev = NULL;

	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)) && curr->key[ft_strlen(key)] == '\0')
		{
			if (prev) // ortadaysa ya da sondaysa
				prev->next = curr->next;
			else      // head ise
				*env = curr->next;

			free(curr->key);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

