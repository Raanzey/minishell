# include "../../minishell.h"

t_env *init_env(char **env)
{
	t_env *head = NULL;
	t_env *tail = NULL;
	t_env *node;
	int i = 0;

	while (env[i])
	{
		char *eq = ft_strchr(env[i], '=');
		if (!eq)
		{
			i++;
			continue;
		}
		int key_len = eq - env[i];
		node = malloc(sizeof(t_env));
		if (!node)
			return NULL;
		node->key = ft_substr(env[i], 0, key_len);
		node->value = ft_strdup(eq + 1);
		node->next = NULL;
		if (!head)
		{
			head = node;   // ilk node
			tail = node;
		}
		else
		{
			tail->next = node; // sıraya ekle
			tail = node;
		}
		i++;
	}
	return head;
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
	free(node->value);               // Önce eski değeri temizle
	node->value = ft_strdup(value);  // Yeni değeri kopyala
}
void append_env(t_env *env, const char *key, const char *value)
{
	t_env *new;
	t_env *tail;
	// Yeni node oluştur
	new = malloc(sizeof(t_env));
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
void add_or_update_env(t_env *env, char *eq, char *av)
{
	int key_len;
	char *key;
	char *val;

	key_len = eq - av; 
	key = ft_substr(av, 0, key_len);// "KEY" ve "VALUE" kısımlarını ayır
	val = ft_strdup(eq + 1); // '=' karakterinden sonrasını al

	// KEY varsa node'u bul
	t_env *node = find_env(env, key);
	if (node)
		update_env(node, val);       // varsa güncelle
	else
		append_env(env, key, val);  // yoksa ekle

	// Bellek temizliği
	free(key);
	free(val);
}
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

