#include "../minishell.h"

static size_t	world_count(char const *s, size_t wc, size_t i)
{
        char quote;

	while (s[i])
	{
		if (s[i] == '\'' || s[i] ==  '"')
                {
                        quote = s[i++];
                        while (s[i] && s[i] != quote)
                                i++;
                        if (!s[i])
                                error(); // tırnak kapanmıyor
                        wc++;
                }
                else
                {
                        while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
                                i++;
                        while (s[i] != 32 || !(s[i] >= 9 && s[i] <= 13) || s[i] != '<' || s[i] != '>' || s[i] != '|')
                                i++;
                        wc++;
                        if (s[i] == '<' || (s[i] == '<' && s[i + 1] == '<') || s[i] == '>' || (s[i] == '>' && s[i + 1] == '>') || s[i++] == '|')
                                wc++;
                }
	}
	return (wc);
}

static int	free_tab(char **sp)
{
	size_t	i;

	i = 0;
	if (sp)
	{
		while (sp[i])
		{
			free(sp[i]);
			i++;
		}
		free(sp);
	}
        return (NULL);
}

static char	**last_sp(char **sp, char const *s, size_t wc, size_t	j)
{
	size_t	i;
        char quote;

	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == '\'' || s[i] ==  '"')
                {
                        quote = s[i++];
                        while (s[i + j] && s[i + j] != quote)
                                j++;
                        sp[wc] = ft_substr(s, i, j);
                        if  (!sp[wc++])
                                return (free_tab(sp));
                        if (!s[i + j])
                                error(); // tırnak kapanmıyor
                }
                else
                {
                        while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
                                i++;
                        while (s[i + j] != 32 || !(s[i + j] >= 9 && s[i + j] <= 13) || s[i + j] != '<' || s[i + j] != '>' || s[i + j] != '|')
                                j++;
                        sp[wc] = ft_substr(s, i, j); //TODO şart lazım
                        if  (!sp[wc++])
                                return (free_tab(sp));
                        i = j; //TODO şart lazıım
                        if (s[i] == '<' || (s[i] == '<' && s[i + 1] == '<') || s[i] == '>' || (s[i] == '>' && s[i + 1] == '>') || s[i++] == '|')
                                wc++;
                }
	}
	return (sp);
}

char	**tokenizer(char const *s)
{
	char	**tokens;
	size_t	wc;

	wc = world_count(s, 0, 0);
	tokens = ft_calloc(wc + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	if (!last_sp(tokens, s, 0, 0))
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