//HEADER

#include "parsing.h"

bool	nb_word_env(char *str, int *word, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
			&& (str[i + 1] == ' ' || (str[i + 1] >= '\t'
					&& str[i + 1] <= '\r')))
			*word += 1;
		i++;
	}
	if ((str[i - 1] == ' ' || (str[i - 1] >= '\t' && str[i - 1] <= '\r'))
		&& c == '\0')
        return (true);
    return (false);
}

void	in_quotes(char *data, t_exp *var)
{
	char	quotetype;

	quotetype = data[var->j];
	var->j += 1;
	while (data[var->j] && data[var->j] != quotetype)
		var->j += 1;
}

void	check_var_env(char *data, t_env **env, t_exp *var)
{
	int	len;

	while (!var->str && data[var->j] && data[var->j] == '$')
	{
		var->str = search_env(data + (var->j + 1), env);
		if (!var->str)
		{
			var->j += 1;
			var->null += 1;
			while (data[var->j] && data[var->j] != '$' && data[var->j] != '"'
				&& data[var->j] != '\'')
			{
				var->null += 1;
				var->j += 1;
			}
		}
	}
	if (var->null == (int)ft_strlen(data))
		var->dollar = true;
	var->null++;
	len = (int)ft_strlen(var->tmp) - 1;
	if (!var->str && data[var->j] == '\0' && (var->j - var->null) > 0
		&& data[var->j - var->null] < 0 && var->tmp && (var->tmp[len] == ' '
		|| (var->tmp[len] >= '\t' && var->tmp[len] <= '\r')))
		var->dollar = true;
}

void	var_env(char *data,  int *word, t_exp *var)
{
	int	len;

	len = 0;
	if (var->j != 0 && (var->j - var->null) > 0 && data[var->j - var->null] < 0)
	{
		len = (int)ft_strlen(var->tmp) - 1;
		if (var->tmp && var->tmp[len] != ' ' && (var->tmp[len] < '\t' || var->tmp[len] > '\r')
			&& (var->str && (var->str[0] == ' ' || (var->str[0] >= '\t' && var->str[0] <= '\r'))))
			*word += 1;
	}
	if (var->j != 0 && (var->j - var->null) > 0 && data[var->j - var->null] > 0
		&& ((var->str && (var->str[0] == ' ' || (var->str[0] >= '\t' && var->str[0] <= '\r')))))
		*word += 1;
	var->j += 1;
	while (data[var->j] && data[var->j] != '$' && data[var->j] != '"'
		&& data[var->j] != '\'')
	{
		data[var->j] *= -1;
		var->j += 1;
	}
}

void	in_dollar(char *data, t_env **env, int *word, t_exp *var)
{
	var->null = 0;
	check_var_env(data, env, var);
	if (var->str)
	{
		var_env(data, word, var);
		var->dollar = nb_word_env(var->str, word, data[var->j]);
		var->tmp = var->str;
		var->str = NULL;
	}
}

void	revert(char **data)
{
	int	i;
	int	j;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] < 0)
				data[i][j] *= -1;
			j++;
		}
		i++;
	}
}

void	nb_word(char **data, t_env **env, int *word)
{
	t_exp	var;
	int		i;

	i = 0;
	var.null = 0;
	var.str = NULL;
	var.tmp = NULL;
	while (data[i])
	{
		var.dollar = false;
		var.j = 0;
		while (data[i][var.j])
		{
			if (data[i][var.j] == '"' || data[i][var.j] == '\'')
				in_quotes(data[i], &var);
			if (data[i][var.j] == '$')
				in_dollar(data[i], env, word, &var);
			else if (data[i][var.j])
				var.j++;
		}
		if (var.dollar == false)
            *word += 1;
		i++;
	}
	revert(data);
}
