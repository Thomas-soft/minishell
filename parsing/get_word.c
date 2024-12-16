/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:55:22 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 18:51:01 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	get_word3(char *word, char *token_line, t_index *i, t_env *env)
{
	char	quote;

	quote = 0;
	if (is_quote(token_line[i->i]))
		quote = token_line[(i->i)++];
	while (token_line[i->i] && token_line[i->i] != quote && quote != 0)
	{
		if (is_dollar(token_line[i->i]) && quote == '\"')
		{
			if (get_env_token2(token_line, word, i, env) == -1)
				return (-1);
		}
		else
			word[(i->k)++] = token_line[(i->i)++];
	}
	return (quote);
}

static int	get_word2(char *word, char *token_line, t_index *i, t_env *env)
{
	char	quote;

	while (token_line[i->i] && token_line[i->i] != ' ')
	{
		quote = 0;
		while (token_line[i->i] && token_line[i->i] != ' '
			&& !is_quote(token_line[i->i]) && !is_dollar(token_line[i->i]))
			word[(i->k)++] = token_line[(i->i)++];
		if (is_dollar(token_line[i->i]))
		{
			if (get_env_token2(token_line, word, i, env) == -1)
				return (-1);
		}
		quote = get_word3(word, token_line, i, env);
		if (quote == -1)
			return (-1);
		if (token_line[i->i] == quote && quote != 0)
			i->i += 1;
	}
	word[i->k] = 0;
	return (0);
}

char	*get_word(char *token_line, int *index, t_env *env)
{
	char	*word;
	int		res;
	t_index	i;

	init_index(&i);
	i.i = *index;
	res = len_word(token_line + i.i, env);
	if (res == -1)
		return (NULL);
	word = malloc(sizeof(char) * (res + 1));
	if (word == NULL)
		return (NULL);
	if (get_word2(word, token_line, &i, env) == -1)
	{
		free(word);
		return (NULL);
	}
	*index = i.i;
	return (word);
}
