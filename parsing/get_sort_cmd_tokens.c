/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sort_cmd_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:24:12 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 17:22:32 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_tab_cmd(t_token *token, t_env *env, char **tab, t_index *i)
{
	i->j = 0;
	while (token->tab[i->j])
	{
		if (i->j == 0)
			tab[i->k++] = get_cmd_path(token->tab[i->j++], env);
		else
			tab[i->k++] = ft_strdup(token->tab[i->j++]);
		if (tab[i->k - 1] == NULL)
		{
			err_free_2d_char(tab, i->k - 2);
			return (0);
		}
	}
	return (1);
}

int	fill_tab_arg_cmd(t_token *token, t_env *env, char **tab, t_index *i)
{
	i->j = 1;
	while (token->tab[0] && token->tab[1] && token->tab[i->j])
	{
		if (i->j == 1)
			tab[i->k++] = get_cmd_path(token->tab[i->j++], env);
		else
			tab[i->k++] = ft_strdup(token->tab[i->j++]);
		if (tab[i->k - 1] == NULL)
		{
			err_free_2d_char(tab, i->k - 2);
			return (0);
		}
	}
	return (1);
}

int	fill_arg(t_token **tokens, char **tab, t_index *i)
{
	i->i += 1;
	while ((tokens[i->i]) && (!is_pr_token(tokens[i->i]->tab)
			|| tokens[i->i]->tab[0][0] != '|'))
	{
		i->j = 1;
		while (tokens[i->i]->tab[0] && tokens[i->i]->tab[1]
			&& tokens[i->i]->tab[i->j])
		{
			tab[(i->k)++] = ft_strdup(tokens[i->i]->tab[(i->j)++]);
			if (tab[i->k - 1] == NULL)
			{
				err_free_2d_char(tab, i->k - 2);
				return (-1);
			}
		}
		i->i += 1;
	}
	return (0);
}

char	**get_cmd_sort(t_token **tokens, t_env *env)
{
	t_index	i;
	char	**tab;

	init_index(&i);
	tab = initialize_tab(tokens, &i);
	if (!tab)
		return (NULL);
	if (tokens[i.i]->type == CMD)
	{
		if (!fill_tab_cmd(tokens[i.i], env, tab, &i))
			return (NULL);
	}
	else if (tokens[i.i]->type == ARG_CMD)
	{
		if (!fill_tab_arg_cmd(tokens[i.i], env, tab, &i))
			return (NULL);
	}
	if (fill_arg(tokens, tab, &i) == -1)
	{
		free_2d_char(tab);
		return (NULL);
	}
	tab[i.k] = NULL;
	return (tab);
}

t_token	*get_sort_cmd_tokens(t_token **tokens, t_env *env)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->tab = get_cmd_sort(tokens, env);
	if (token->tab == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = CMD;
	return (token);
}
