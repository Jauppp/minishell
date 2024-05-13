/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:48:21 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 19:29:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	search_dollar_hd(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	heredoc_expand(char **line, t_input *in)
{
	char	*str;
	char	*temp;
	size_t	letter;

	str = NULL;
	temp = NULL;
	str = ft_itoa(in->status);
	if (!str)
		return (print_error(errno, NULL), 1);
	letter = nb_letter(*line, &(in)->env, str);
	temp = ft_calloc(sizeof(char), letter + 1);
	if (!temp)
		return (free(str), print_error(errno, NULL), 1);
	ft_copy(*line, temp, &(in)->env, str);
	letter = 0;
	// dprintf(2, "temp: %s\n", temp);
	// dprintf(2, "line 1: %s\n", *line);
	while (temp[letter])
	{
		if (temp[letter] < 0)
			temp[letter] *= -1;
		letter++;
	}
	free(*line);
	*line = temp;
	// dprintf(2, "line 2: %s\n", *line);
	free(str);
	return (0);
}
