/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:16:19 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/26 19:16:06 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_parsed_token(char *token_line, t_env *env)
{
	char	*new_token_line;
	int		res;

	res = len_env_token(token_line, env);
	if (res == -1)
		return (NULL);
	new_token_line = malloc(sizeof(char) * (res + 1));
	if (new_token_line == NULL)
		return (NULL);
	if (get_env_token(new_token_line, token_line, env) == -1)
	{
		free(new_token_line);
		return (NULL);
	}
	return (new_token_line);
}

int	get_splited_token2(char *token_line, char **tab, t_env *env, t_index *i)
{
	while (token_line[i->i])
	{
		while (token_line[i->i] && token_line[i->i] == ' ')
			i->i += 1;
		tab[i->j] = get_word(token_line, &i->i, env);
		if (tab[i->j] == NULL)
		{
			err_free_2d_char(tab, i->j - 1);
			return (-1);
		}
		while (token_line[i->i] && token_line[i->i] == ' ')
			i->i += 1;
		i->j += 1;
	}
	return (0);
}

static char	**get_splited_token(char *token_line, t_env *env)
{
	t_index	i;
	char	**tab;

	init_index(&i);
	tab = malloc(sizeof(char *) * (count_word(token_line) + 1));
	if (tab == NULL)
		return (NULL);
	if (count_word(token_line) == 0)
	{
		tab[0] = NULL;
		return (tab);
	}
	if (get_splited_token2(token_line, tab, env, &i) == -1)
		return (NULL);
	tab[i.j] = NULL;
	return (tab);
}

t_token	*split_word(char *token_line, t_env *env)
{
	t_token	*token;
	char	*new_token_line;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	new_token_line = get_parsed_token(token_line, env);
	if (new_token_line == NULL)
	{
		free_2d_char(token->tab);
		free(token);
		return (NULL);
	}
	token->tab = get_splited_token(new_token_line, env);
	if (token->tab == NULL)
	{
		free(new_token_line);
		free(token);
		return (NULL);
	}
	free(new_token_line);
	return (token);
}
