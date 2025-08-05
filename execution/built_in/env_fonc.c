# include "../../minishell.h"

t_env *init_env(char **env, int i)
{
	t_env *env_list;
	char *eq;
	int key_len;
	char *key;
	char *val;
	i = 0;
	env_list = NULL;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (!eq)
		{
			i++;
			continue;
		}
		key_len = eq - env[i];
		key = ft_substr(env[i], 0, key_len);
		val = ft_strdup(eq + 1);
		insert_sorted_env(&env_list, key, val);
		// free(key);
		// free(val);
		i++;
	}
	return env_list;
}
t_env *find_env(t_env *env, const char *key)
{
	while (env)
	{
		// Tam eşleşme kontrolü
		if (!ft_strncmp(env->key, key,ft_strlen(env->key)))
			return env;
		env = env->next;
	}
	return NULL;
}
void update_env(t_env *node, const char *value)
{
	if (!node)
		return;
	// free(node->value);               // Önce eski değeri temizle
	node->value = ft_strdup(value);  // Yeni değeri kopyala
}
void append_env(t_env *env, const char *key, const char *value)
{
	t_env *new;
	t_env *tail;
	// Yeni node oluştur
	new = ft_malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;

	//printf("%s = %s", new->key, new->value);
	if (!env)
		env = new; // Liste boşsa bu ilk eleman olur
	else
	{
		tail = env;
		// Listenin sonuna git
		while (tail->next)
			tail = tail->next;
		tail->next = new; // Yeni elemanı sona ekle
	}
}
void add_or_update_env(t_env **env, char *eq, char *av)
{
	int key_len = eq - av;
	char *key = ft_substr(av, 0, key_len);
	char *val = ft_strdup(eq + 1);

	insert_sorted_env(env, key, val);

	// free(key);
	// free(val);
}

