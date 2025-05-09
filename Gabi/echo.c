#include "minishell.h"

void	cmd_echo(t_token *start, t_token *end)
{
	int	nl;

	nl = 1;
	if (strcmp(start->value, "-n") == 0)
		nl = 0;
	start = start->next;
	while (start && start != end)
	{
		printf("%s", start->value);
		if (start->has_leading_space)
			printf(" ");
		start = start->next;
	}
	if (nl)
		printf("\n");
}