#include "../minishell.h"

void    cmd_cd(char *str)
{
    char buf[1024];
    char *cur_dir;

    if (!chdir(str))
    {
        cur_dir = getcwd(buf, sizeof(buf));
        if (!cur_dir)
        {
            perror("chdir error");
            return ;
        }
        else
            printf("New current directory: %s\n", cur_dir);
    }
}

// int main(int ac, char **ag)
// {
//     cmd_cd("03_builtin");
//     return 0;
// }