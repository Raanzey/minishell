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

char *remove_quotes(char *s)
{
        char *new;
        size_t i;
        size_t j;
        char quote;

        i = 0;
        j = 0;
        new = ft_calloc(ft_strlen(s) + 1), sizeof(char);
        if (!new)
                return (NULL);
        while (s[i])
        {
                if (s[i] == '"' || s[i] == '\'')
                {
                        quote = str[i++];
                        while (s[i] && s[i] != quote)
                                new[j++] = s[i++];
                        if (s[i] == quote)
                                i++;
                }
                else
                        new[j++] = str[i++];
        }
        return (new);
}

char *expand_dollar(char *s, int last_exit)
{
        char *res;
        char *key;
        char * val;
        size_t i;
        size_t j;

        i = 0;
        res = ft_calloc(1, 1);
        while (s[i])
        {
                if (s[i] == '$')
                {
                        if (s[i + 1] == '?')
                        {
                                res = ft_strjoin_free(res, ft_itoa(last_exit)); //TODO ekle
                                i += 2;
                        }
                        else if (ft_isalpha(s[i + 1]) || s[i + 1] == '_')
                        {
                                j = i + 1;
                                while (s[j] && (ft_isalnum(s[j] || s[j] == '_')))
                                        j++;
                                key = ft_substr(s, i + 1, j - (i + 1));
                                val = getenv(key);
                                res = ft_strjoin_free(res, val ? val : ""); //TODO ekle
                                free(key);
                                i = j;
                        }
                        else
                                res = ft_strjoin_char(res,s[i++]); //TODO ekle
                }
                res = ft_strjoin_char(res, s[i++]); //TODO ekle
        }
        return (res);
}

void expand_args(t_command *cmd)
{

}