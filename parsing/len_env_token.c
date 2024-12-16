/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_env_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:12:58 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 16:44:30 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_env_token4(char *token_line, int start, t_env *env, int *i)
{
	int		len;
	char	*temp;
	char	*value;

	len = 0;
	while (token_line[*i] && (ft_isalpha(token_line[*i])
			|| ft_isalnum(token_line[*i]) || token_line[*i] == '_'))
		*i += 1;
	temp = ft_substr(token_line + start, 0, *i - start);
	if (temp == NULL)
		return (-1);
	value = getenv_value(temp, env);
	if (value == NULL)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	if (value != NULL)
		len += ft_strlen(value);
	free(value);
	return (len);
}

int	len_env_token2(char *token_line, int *i, int *len, t_env *env)
{
	int	start;
	int	res;

	res = 0;
	start = ++(*i);
	if (!token_line[start] || token_line[start] == ' ')
		*len += 1;
	else if (token_line[start] && token_line[start] == '?')
	{
		*i += 1;
		*len += ft_nblen(g_var);
	}
	else
	{
		res = len_env_token4(token_line, start, env, i);
		if (res == -1)
			return (-1);
		*len += res;
	}
	return (0);
}

static void	len_env_token3(char *token_line, int *i, int *len)
{
	*i += 1;
	*len += 1;
	while (token_line[*i] && token_line[*i] != '\'')
	{
		*i += 1;
		*len += 1;
	}
	if (token_line[*i] == '\'')
	{
		*i += 1;
		*len += 1;
	}
}

int	len_env_token(char *token_line, t_env *env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token_line[i])
	{
		while (token_line[i] && token_line[i] != '$' && token_line[i] != '\'')
		{
			i++;
			len++;
		}
		if (!token_line[i])
			return (len);
		if (token_line[i] == '$')
		{
			if (len_env_token2(token_line, &i, &len, env) == -1)
				return (-1);
		}
		else
			len_env_token3(token_line, &i, &len);
	}
	return (len);
}
