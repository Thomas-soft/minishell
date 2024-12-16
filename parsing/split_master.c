/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:50:18 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/21 17:10:06 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	split_token2(t_token **tokens, t_env *env, char *token_line,
		char *line)
{
	t_index	i;

	init_index(&i);
	while (line[i.i])
	{
		while (line[i.i] && line[i.i] == ' ')
			i.i += 1;
		token_line = get_token(line, &i);
		if (token_line == NULL)
		{
			err_free_token(tokens, i.j - 1, 1);
			return (-1);
		}
		tokens[i.j++] = split_word(token_line, env);
		if (tokens[i.j - 1] == NULL)
		{
			free(token_line);
			err_free_token(tokens, i.j - 2, 1);
			return (-1);
		}
		while (line[i.i] && line[i.i] == ' ')
			i.i += 1;
		free(token_line);
	}
	return (0);
}

static t_token	**split_token(char *line, t_env *env)
{
	t_index	i;
	t_token	**tokens;
	char	*token_line;

	token_line = NULL;
	init_index(&i);
	tokens = malloc(sizeof(t_token *) * (count_token(line) + 1));
	if (tokens == NULL)
		return (NULL);
	if (split_token2(tokens, env, token_line, line) == -1)
		return (NULL);
	tokens[count_token(line)] = NULL;
	return (tokens);
}

t_token	**split_master(char *line, t_env *env, int *res)
{
	t_token	**tokens;
	t_token	**new_tokens;

	tokens = split_token(line, env);
	if (tokens == NULL)
		return (NULL);
	put_types(tokens);
	if (good_pos_pr(tokens) == -1)
	{
		free_token(tokens, 1);
		ft_putstr_fd("Invalid pipe/redirection/quote\n", 2);
		*res = 1;
		return (NULL);
	}
	new_tokens = sort_tokens(tokens, env);
	if (new_tokens == NULL)
	{
		free_token(tokens, 1);
		free(line);
		return (NULL);
	}
	free_token(tokens, 1);
	return (new_tokens);
}
