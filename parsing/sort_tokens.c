/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:57:44 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 17:02:12 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	**handle_error(t_token **new_tokens, int index)
{
	err_free_token(new_tokens, index - 1, 1);
	return (NULL);
}

static t_token	*get_pipe(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->tab = malloc(sizeof(char *) * 2);
	if (token->tab == NULL)
	{
		free(token);
		return (NULL);
	}
	token->tab[0] = ft_strdup("|");
	if (token->tab[0] == NULL)
	{
		free(token);
		return (NULL);
	}
	token->tab[1] = NULL;
	token->type = PR;
	return (token);
}

static int	update_index(t_token **tokens, t_token **new_tokens, t_index *i)
{
	i->k += 1;
	i->i += 1;
	i->doll = 0;
	if (has_arg_cmd(tokens))
		i->doll = -1;
	if (tokens[i->i + i->doll] && tokens[i->i + i->doll]->tab[0]
		&& tokens[i->i + i->doll]->tab[0][0] == '|'
		&& is_pr_token(tokens[i->i + i->doll]->tab))
	{
		new_tokens[i->i] = get_pipe();
		if (new_tokens[i->i] == NULL)
		{
			err_free_token(new_tokens, i->i - 1, 1);
			return (-1);
		}
		i->i += 1;
		while ((tokens[i->j]) && (!is_pr_token(tokens[i->j]->tab)
				|| tokens[i->j]->tab[0][0] != '|'))
			i->j += 1;
		if (tokens[i->j] && tokens[i->j]->tab[0][0] == '|'
			&& is_pr_token(tokens[i->j]->tab))
			i->j += 1;
		i->k = 0;
	}
	return (0);
}

static int	should_get_sort_cmd(t_token **tokens, t_index *i)
{
	if (i->k == 0 && ((has_cmd(tokens + i->j)) || (i->j > 0 && tokens[i->j
					- 1]->tab[0][0] == '|'
			&& is_pr_token(tokens[i->j - 1]->tab))))
		return (1);
	return (0);
}

t_token	**sort_tokens(t_token **tokens, t_env *env)
{
	t_index	i;
	t_token	**new_tokens;
	int		res;

	res = sort_count_tokens(tokens);
	if (res == -1)
		return (NULL);
	init_index(&i);
	new_tokens = malloc(sizeof(t_token *) * (res + 1));
	if (new_tokens == NULL)
		return (NULL);
	while (i.i < res)
	{
		if (should_get_sort_cmd(tokens, &i))
			new_tokens[i.i] = get_sort_cmd_tokens(tokens + i.j, env);
		else
			new_tokens[i.i] = get_sort_tokens(tokens + i.j, i.k);
		if (new_tokens[i.i] == NULL)
			return (handle_error(new_tokens, i.i - 1));
		if (update_index(tokens, new_tokens, &i) == -1)
			return (NULL);
	}
	new_tokens[i.i] = NULL;
	return (new_tokens);
}
