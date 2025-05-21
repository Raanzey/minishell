#include "../minishell.h"

static size_t	world_count(char const *s, size_t wc, size_t i)
{
        char quote;

	while (s[i])
	{
                while (s[i] == ' ')
                        i++;
                if (!s[i])
                        break;
                if (s[i] == '\'' || s[i] == '"')
                {
                        quote = s[i++];
                        while (s[i] && s[i] != quote)
                                i++;
                        if (s[i])
                                i++;
                }
                else
                {
                        while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
                                i++;
                }
                wc++;
	}
	return (wc);
}

static char	**last_sp(char **sp, char const *s, size_t wc, size_t i)
{
	size_t	start;
        char quote;

	start = 0;
        while (s[i])
        {
                while (s[i] == ' ')
                        i++;
                if (!s[i])
                        break;
                start = i;
                if (s[i] == '\'' || s[i] == '"')
                {
                        quote = s[i++];
                        start = i;
                        while (s[i] && s[i] != quote)
                                i++;
                        sp[wc++] = ft_substr(s, start, i - start);
                        if (s[i])
                                i++;
                }
                else
                {
                        while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
                                i++;
                        sp[wc++] = ft_substr(s, start, i -start);
                }
        }
        sp[wc] = NULL;
	return (sp);
}

char	**tokenizer(char const *s)
{
	char	**tokens;
	size_t	wc;

	wc = world_count(s, 32, 0);
	tokens = ft_calloc(wc + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	if (!last_sp(tokens, s, 32, 0))
		return (NULL);
	return (tokens);
}






















// #include "../minishell.h"

// static size_t	world_count(char const *s, size_t wc)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == ' ')
// 			i++;
// 		else
// 		{
//                         while (s[i] && s[i] == 34)
//                         {
//                                 if (s[++i] == 34)
//                                         break;
//                         }
//                         while (s[i] && s[i] == 39)
//                         {
//                                 if (s[++i] == 39)
//                                         break;
//                         }
// 			while (s[i] && s[i] != ' ')
// 				i++;
// 			wc++;
// 		}
// 	}
// 	return (wc);
// }

// static size_t	control(char const *s, size_t start, size_t i)
// {
// 	if (s[start + i])
// 		return (1);
// 	return (0);
// }

// static void	free_tab(char **sp)
// {
// 	size_t	i;

// 	i = 0;
// 	if (sp)
// 	{
// 		while (sp[i])
// 		{
// 			free(sp[i]);
// 			i++;
// 		}
// 		free(sp);
// 	}
// }

// static char	**last_sp(char **sp, char const *s, size_t wc)
// {
// 	size_t	start;
// 	size_t	i;

// 	i = 0;
// 	start = 0;
// 	while (s[start])
// 	{
// 		i = 0;
// 		while (s[start + i] && s[start + i] != ' ' && (s[start] == 34 || s[start] == 39))
//                 {
//                         if (s[start + i++] == s[start])
//                                 break;
//                 }
// 		if (i > 0)
// 		{
// 			sp[wc] = ft_substr(s, start, i);
// 			if (!sp[wc++])
// 			{
// 				free_tab(sp);
// 				return (NULL);
// 			}
// 		}
// 		start += i + control(s, start, i);
// 	}
// 	return (sp);
// }

// char	**tokenizer(char const *s)
// {
// 	char	**tokens;
// 	size_t	wc;

// 	wc = world_count(s, 32);
// 	tokens = ft_calloc(wc + 1, sizeof(char *));
// 	if (!tokens)
// 		return (NULL);
// 	if (!last_sp(tokens, s, 32))
// 		return (NULL);
// 	return (tokens);
// }