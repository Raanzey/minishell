/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:16:15 by musisman          #+#    #+#             */
/*   Updated: 2025/06/05 09:16:15 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*remove_quotes(const char *str)
{
	char	*res;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				res[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			res[j++] = str[i++];
	}
	return (res);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*res;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, len);
	res[len] = c;
	res[len + 1] = '\0';
	free(s);
	return (res);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	free(s1);
	return (res);
}

char	*extract_var_name(const char *str, size_t *i)
{
	size_t	start;
	char	*var;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	return (var);
}

char	*expand_dollar(const char *s, int last_exit)
{
	size_t	i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_calloc(1, 1);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			tmp = ft_itoa(last_exit);
			res = ft_strjoin_free(res, tmp);
			free(tmp);
			i += 2;
		}
		else if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
		{
			i++;
			tmp = extract_var_name(s, &i);
			tmp = ft_strjoin_free(res, getenv(tmp) ?: "");
			res = tmp;
		}
		else
			res = ft_strjoin_char(res, s[i++]);
	}
	return (res);
}


// char *expand_dollar(char *s, int last_exit)
// {
//         char *res;
//         char *key;
//         char * val;
//         size_t i;
//         size_t j;

//         i = 0;
//         res = ft_calloc(1, 1);
//         while (s[i])
//         {
//                 if (s[i] == '$')
//                 {
//                         if (s[i + 1] == '?')
//                         {
//                                 res = ft_strjoin_free(res, ft_itoa(last_exit)); //TODO ekle gerek yok sanırım free zaten en son yapılacak
//                                 i += 2;
//                         }
//                         else if (ft_isalpha(s[i + 1]) || s[i + 1] == '_')
//                         {
//                                 j = i + 1;
//                                 while (s[j] && (ft_isalnum(s[j] || s[j] == '_')))
//                                         j++;
//                                 key = ft_substr(s, i + 1, j - (i + 1));
//                                 val = getenv(key);
//                                 res = ft_strjoin_free(res, val ? val : ""); //TODO ekle
//                                 free(key);
//                                 i = j;
//                         }
//                         else
//                                 res = ft_strjoin_char(res,s[i++]); //TODO ekle
//                 }
//                 res = ft_strjoin_char(res, s[i++]); //TODO ekle
//         }
//         return (res);
// }

char	*expand_token(char *token, int last_exit)
{
	char	*tmp;
	char	*res;

	if (!token)
		return (NULL);
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		return (remove_quotes(token));
	if (token[0] == '"' && token[ft_strlen(token) - 1] == '"')
	{
		tmp = remove_quotes(token);
		res = expand_dollar(tmp, last_exit);
		free(tmp);
		return (res);
	}
	return (expand_dollar(token, last_exit));
}

void	expand_args(t_command *cmd, int last_exit)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->av && cmd->av[i])
		{
			tmp = expand_token(cmd->av[i], last_exit);
			free(cmd->av[i]);
			cmd->av[i] = tmp;
			i++;
		}
		cmd = cmd->next;
	}
}

void	expand_redirections(t_command *cmd, int last_exit)
{
	t_redirect	*r;
	char		*tmp;

	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			tmp = expand_token(r->filename, last_exit);
			free(r->filename);
			r->filename = tmp;
			r = r->next;
		}
		cmd = cmd->next;
	}
}
