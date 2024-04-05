//HEADER

#include "parsing.h"

bool	nb_word_env(char *str, int *word, char c)
{
	int		i;

	// (void)c;
	i = 0;
	if (!str || !str[0])
		return (false);
	// printf("str : %s\n", str);
	while (str[i])
	{
		if ((str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
			&& (/*str[i + 1] == '\0' || */str[i + 1] == ' ' || (str[i + 1] >= '\t'
					&& str[i + 1] <= '\r')))
			*word += 1;
		i++;
	}
	if ((str[i - 1] == ' ' || (str[i - 1] >= '\t' && str[i - 1] <= '\r')) && c == '\0')//(c != '"' && c != '\''))
    {
        // if (c == '"' || c == '\'')
		//     *word += 1;
        return (true);
    }
    return (false);
	// *word -= 1;
}

void	nb_word(char **data, t_env **env, int *word)
{
	int		i;
	int		j;
	char	quotetype;
	char	*str;
	char	*tmp;
	int		len;
	bool	dollar;

	i = 0;
	len = 0;
	str = NULL;
	tmp = NULL;
	while (data[i])
	{
		dollar = false;
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] == '"' || data[i][j] == '\'')
			{
				quotetype = data[i][j++];
				while (data[i][j] && data[i][j] != quotetype)
					j++;
			}
			if (data[i][j] == '$')
			{
				str = search_env(data[i] + (j + 1), env);
				if (j != 0 && data[i][j - 1] < 0)
				{
					len = ft_strlen(tmp) - 1;
					if (tmp[len] != ' ' && (tmp[len] < '\t' || tmp[len] > '\r') && (str && (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r'))))
						*word += 1;
				}
				tmp = str;
				// dollar = true;
				if (j != 0 && data[i][j - 1] > 0 && (/*(!str || !str[0]) || */(str && (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r')))))
					*word += 1;
				j++;
				while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
					&& data[i][j] != '\'')
				{
					data[i][j] *= -1;
					j++;
				}
				dollar = nb_word_env(str, word, data[i][j]);
			}
			else if (data[i][j])
				j++;
		}
		if (dollar == false)
            *word += 1;
		i++;
	}
}