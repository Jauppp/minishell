/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:33:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 11:22:24 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_freelst(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		free(env->env);
		tmp = env->next;
		free(env);
		env = tmp;
	}
	env = NULL;
}

void	env_addback(t_env **env, t_env *node)
{
	t_env	*head;

	if (!node || !env)
		return ;
	if (!*env)
		*env = node;
	else
	{
		head = (*env);
		while ((*env)->next)
			(*env) = (*env)->next;
		(*env)->next = node;
		node->prev = (*env);
		(*env) = head;
	}
}

t_env	*env_newnode(char *data)
{
	t_env	*node;

	node = malloc(1 * sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	node->env = ft_strdup(data);
	if (!node->env)
		exit(EXIT_FAILURE);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
