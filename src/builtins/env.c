//HEADER

#include "exec.h"

int	env(t_input *node)
{
	if (node->data[1])
	{
		if (ft_putstr_fd("minishell : env : too many arguments\n", 2) == -1)
			return (1);
		return (0); //????
	}
	return (0);
}