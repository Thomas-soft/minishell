/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sort_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:13:12 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 17:03:26 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_arg_sort2(t_token **tokens, int *l, int *r)
{
	while (tokens[*l] && !(tokens[*l] && tokens[*l]->type == PR
			&& ft_strncmp(tokens[*l]->tab[0], "<", 1) == 0) && !(*l > 0
			&& tokens[*l] && tokens[*l - 1]->type == PR && ft_strncmp(tokens[*l
					- 1]->tab[0], "<", 1) == 0) && (tokens[*l]->type != PR
			|| tokens[*l]->tab[0][0] != '|'))
		*l += 1;
	if (tokens[*l] && is_pr_token(tokens[*l]->tab) && tokens[*l + 1]
		&& tokens[*l + 1]->tab[0] == NULL)
		*l += 2;
	while (tokens[*r] && !(tokens[*r] && tokens[*r]->type == PR
			&& ft_strncmp(tokens[*r]->tab[0], ">", 1) == 0) && !(*r > 0
			&& tokens[*r] && tokens[*r - 1]->type == PR && ft_strncmp(tokens[*r
					- 1]->tab[0], ">", 1) == 0) && (tokens[*r]->type != PR
			|| tokens[*r]->tab[0][0] != '|'))
		*r += 1;
	if (tokens[*r] && is_pr_token(tokens[*r]->tab) && tokens[*r + 1]
		&& tokens[*r + 1]->tab[0] == NULL)
		r += 2;
}

static char	*get_arg_sort3(t_token **tokens, int *l, int *r)
{
	char	*str;

	if (tokens[*l] && tokens[*l]->type == PR && ft_strncmp(tokens[*l]->tab[0],
			"<", 1) == 0)
		str = ft_strdup(tokens[(*l)++]->tab[0]);
	else if (*l > 0 && tokens[*l] && tokens[*l]->tab[0] && tokens[*l
			- 1]->type == PR && ft_strncmp(tokens[*l - 1]->tab[0], "<", 1) == 0)
		str = ft_strdup(tokens[(*l)++]->tab[0]);
	else if (tokens[*r] && tokens[*r]->tab[0] && tokens[*r]->type == PR
		&& ft_strncmp(tokens[*r]->tab[0], ">", 1) == 0)
		str = ft_strdup(tokens[(*r)++]->tab[0]);
	else if (*r > 0 && tokens[*r] && tokens[*r]->tab[0] && tokens[*r
			- 1]->type == PR && ft_strncmp(tokens[*r - 1]->tab[0], ">", 1) == 0)
		str = ft_strdup(tokens[(*r)++]->tab[0]);
	else
		return (ft_strdup(""));
	return (str);
}

static char	**get_arg_sort(t_token **tokens, int k)
{
	int			i;
	static int	l = 0;
	static int	r = 0;
	char		**tab;

	tab = malloc(sizeof(char *) * 2);
	if (tab == NULL)
		return (NULL);
	i = 0;
	if ((k == 0) || (k == 1 && has_cmd(tokens)))
	{
		r = 0;
		l = 0;
	}
	while (tokens[i])
		i++;
	get_arg_sort2(tokens, &l, &r);
	tab[0] = get_arg_sort3(tokens, &l, &r);
	if (tab[0] == NULL)
	{
		free(tab);
		return (NULL);
	}
	tab[1] = NULL;
	return (tab);
}

t_token	*get_sort_tokens(t_token **tokens, int k)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->tab = get_arg_sort(tokens, k);
	if (token->tab == NULL)
	{
		free(token);
		return (NULL);
	}
	if (is_pr_token(token->tab))
		token->type = PR;
	else
		token->type = ARG;
	return (token);
}
