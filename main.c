/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/28 17:40:36 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_input	*input;
	char	*line;

	(void)argc;
	(void)argv;
	line = NULL;
	env = NULL;
	input = NULL;
	create_env(&input, envp, &env);
	while (1)
	{
		line = readline("Minishell > ");
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0 && line[0])
		{
			env_freelst(env);
			exit(EXIT_SUCCESS);
		}
		tokenization(&input, &env, line);
		t_input	*temp;
		int i = 1;
		int	j = 0;
		temp = input;
		while (temp)
		{
			printf("\n- - - node %d - - -\n\n", i);
			printf("tok: %d\n", temp->tok);
			if (temp->data)
			{
				j = 0;
				while (temp->data[j])
				{
					printf("data[%d]: %s\n", j, temp->data[j]);
					j++;
				}
			}
			printf("\n- - - - - - - - - -\n\n");
			temp = temp->next;
			i++;
		}
		input_freelst(&input);
	}
	return (0);
}
