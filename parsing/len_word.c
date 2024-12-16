/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:21:47 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 16:27:47 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_word3(char *token_line, int *i, char quote, t_env *env)
{
	int	len;

	len = 0;
	while (token_line[*i] && token_line[*i] != quote && quote != 0)
	{
		if (is_dollar(token_line[*i]) && quote == '\"')
		{
			if (len_env_token2(token_line, i, &len, env) == -1)
				return (-1);
		}
		else
		{
			*i += 1;
			len++;
		}
	}
	return (len);
}

static int	len_word2(char *token_line, int *i, char *quote, t_env *env)
{
	int	len;

	len = 0;
	while (token_line[*i] && token_line[*i] != ' '
		&& !is_quote(token_line[*i]) && !is_dollar(token_line[*i]))
	{
		*i += 1;
		len++;
	}
	if (is_dollar(token_line[*i]))
	{
		if (len_env_token2(token_line, i, &len, env) == -1)
			return (-1);
	}
	if (is_quote(token_line[*i]))
		*quote = token_line[(*i)++];
	return (len);
}

int	len_word(char *token_line, t_env *env)
{
	t_index	i;
	int		len;
	char	quote;

	len = 0;
	init_index(&i);
	while (token_line[i.i] && token_line[i.i] != ' ')
	{
		quote = 0;
		i.j = len_word2(token_line, &i.i, &quote, env);
		if (i.j == -1)
			return (-1);
		len += i.j;
		i.j = len_word3(token_line, &i.i, quote, env);
		if (i.j == -1)
			return (-1);
		len += i.j;
		if (token_line[i.i] == quote && quote != 0)
			i.i++;
	}
	return (len);
}
