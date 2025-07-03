# include "../../minishell.h"

void export_key_only(t_env *env, const char *key)
{
	t_env *new;
	t_env *tail;
	// 1. Anahtar zaten varsa → hiçbir şey yapma
	if (find_env(env, key))
		return;

	// 2. Yeni node oluştur
	new = malloc(sizeof(t_env));
	if (!new)
		return;

	new->key = ft_strdup(key);
	new->value = ft_strdup(""); // Boş string, NULL değil
	new->next = NULL;

	// 3. Listeye ekle
	if (!env)
		env = new;
	else
	{
		tail = env;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
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
