/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:01:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/28 17:28:00 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*split_wsep(char *str, char sep)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!str || !sep)
		return (NULL);
	while (str[i] && str[i] != sep)
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	res = ft_substr(str, 0, i + 1);
	if (!res)
		return (NULL);
	return (res);
}
