#include "minishell.h"

// funtion used to check the end of env_var
// it stops where ch != letter, number or underscore
int if_alnum_underscore(int arg)
{
    if (!ft_isalnum(arg))
        return (arg == '_');
    else
        return (1);
}