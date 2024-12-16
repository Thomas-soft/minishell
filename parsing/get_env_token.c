/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:12:25 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 16:44:37 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_env_token4(char *token_line, char *new_line, t_env *env,
		t_index *i)
{
	char	*temp;
	char	*value;

	i->j = i->i;
	while (token_line[i->i] && (ft_isalpha(token_line[i->i])
			|| ft_isalnum(token_line[i->i]) || token_line[i->i] == '_'))
		i->i += 1;
	temp = ft_substr(token_line + i->j, 0, i->i - i->j);
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
	{
		i->j = 0;
		while (value[i->j])
			new_line[(i->k)++] = value[(i->j)++];
	}
	free(value);
	return (0);
}

int	get_env_token2(char *token_line, char *new_line, t_index *i, t_env *env)
{
	int	start;

	start = ++(i->i);
	if (!token_line[start] || token_line[start] == ' ')
		new_line[(i->k)++] = token_line[start - 1];
	else if (token_line[start] && token_line[start] == '?')
	{
		ft_putnbr_chr(new_line, &i->k, g_var);
		i->i += 1;
	}
	else
	{
		if (get_env_token4(token_line, new_line, env, i) == -1)
			return (-1);
	}
	return (0);
}

static void	get_env_token3(char *new_token_line, char *token_line, t_index *i)
{
	new_token_line[(i->k)++] = token_line[(i->i)++];
	while (token_line[i->i] && token_line[i->i] != '\'')
		new_token_line[(i->k)++] = token_line[(i->i)++];
	if (token_line[i->i] == '\'')
		new_token_line[(i->k)++] = token_line[(i->i)++];
}

int	get_env_token(char *new_token_line, char *token_line, t_env *env)
{
	t_index	i;

	init_index(&i);
	while (token_line[i.i])
	{
		while (token_line[i.i] && token_line[i.i] != '$'
			&& token_line[i.i] != '\'')
			new_token_line[i.k++] = token_line[i.i++];
		if (!token_line[i.i])
		{
			new_token_line[i.k] = 0;
			return (0);
		}
		if (token_line[i.i] == '$')
		{
			if (get_env_token2(token_line, new_token_line, &i, env) == -1)
				return (-1);
		}
		else
			get_env_token3(new_token_line, token_line, &i);
	}
	new_token_line[i.k] = 0;
	return (0);
}
