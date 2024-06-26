/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:42 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 17:18:33 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	len_str(char *str)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]
				&& (str[i + 1] == '"' || str[i + 1] == '\''))
			|| str[i] == '\'' || str[i] == '"')
			i++;
		else if (str[i])
		{
			i++;
			len++;
		}
	}
	return (len);
}

static void	fill_str(char *new, char *str)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]
				&& (str[i + 1] == '"' || str[i + 1] == '\''))
			|| str[i] == '\'' || str[i] == '"')
			i++;
		else if (str[i])
			new[j++] = str[i++];
	}
}

static char	*rm_quotes(char *str)
{
	char		*new;
	size_t		len;

	new = NULL;
	put_in_neg(str, '\'', '"');
	len = len_str(str);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (print_error(errno, "minishell: parsing"));
	fill_str(new, str);
	return (new);
}

int	search_quotes(t_input *node)
{
	ssize_t		i;
	size_t		j;
	char		*temp;

	i = -1;
	if (!node->data)
		return (0);
	while (node->data[++i])
	{
		j = 0;
		while (node->data[i][j])
		{
			if (node->data[i][j] == '"' || node->data[i][j] == '\'')
			{
				temp = rm_quotes(node->data[i]);
				if (!temp)
					return (1);
				free(node->data[i]);
				node->data[i] = temp;
				break ;
			}
			j++;
		}
	}
	return (0);
}
