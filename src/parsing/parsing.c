/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:58:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 17:16:45 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(t_input **input, t_env **env, char *line)
{
	t_input	*node;
	
	node = NULL;
	if (tokenization(input, env, line))
		return ;
	if (input && *input)
	{
		node = *input;
		while (node)
		{
			if (node->tok != heredoc)
				if (check_for_dollar(node))
					expand(node, env);
			node = node->next;
		}
	}
	// remove_quote()
}
