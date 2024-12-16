/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_cmd_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:54 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 17:10:34 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_cmd_sort2(t_token **tokens, t_index *i)
{
	int	len;

	len = 0;
	if (tokens[i->i]->type == CMD)
	{
		while (tokens[i->i]->tab[(i->j)++])
			len++;
	}
	else if (tokens[i->i]->type == ARG_CMD)
	{
		i->j = 1;
		while (tokens[i->i]->tab[0] && tokens[i->i]->tab[1]
			&& tokens[i->i]->tab[(i->j)++])
			len++;
	}
	else
		return (ft_perror("ERROR"));
	return (len);
}

int	len_cmd_sort(t_token **tokens)
{
	t_index	i;
	int		len;

	init_index(&i);
	len = 0;
	while (tokens[i.i] && tokens[i.i]->type != CMD
		&& tokens[i.i]->type != ARG_CMD)
		i.i++;
	if (!tokens[i.i])
		return (-1);
	i.k = len_cmd_sort2(tokens, &i);
	if (i.k == -1)
		return (-1);
	len += i.k;
	i.i++;
	while ((tokens[i.i]) && (!is_pr_token(tokens[i.i]->tab)
			|| tokens[i.i]->tab[0][0] != '|'))
	{
		i.j = 1;
		while (tokens[i.i]->tab[0] && tokens[i.i]->tab[1]
			&& tokens[i.i]->tab[i.j++])
			len++;
		i.i++;
	}
	return (len);
}
