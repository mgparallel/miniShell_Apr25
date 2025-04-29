#include "minishell.h"

int cmd_echo(int argc, char **argv)
{
    int i;
     
    i = 0;
    if (strcmp(argv[0], "-n") == 0)
        i++;
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (i < argc - 1)
            printf(" ");
    }
    if (strcmp(argv[0], "-n") == 0)
        printf("\n");
    return (0);
}

int exec_echo(char **args)
{
    int argc;
    
    argc = 0;
    while (args[argc] != NULL)
        argc++;
    return (cmd_echo(argc, args));
}