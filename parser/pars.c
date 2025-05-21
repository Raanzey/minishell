#include "../minishell.h"

t_command *parser(char *input)
{
        t_command *cmd;
        char **tokens;

        tokens = tokenizer(input);
        int i = -1;

        while (tokens[++i])
                printf("%d. %s\n", i,tokens[i]);
                
        cmd = NULL;
        return (cmd);
}