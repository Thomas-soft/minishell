/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_count_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:59:37 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 17:02:45 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sort_count_tokens(t_token **tokens)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (tokens[i])
	{
		if (tokens[i] && is_pr_token(tokens[i]->tab) && tokens[i + 1]
			&& tokens[i + 1]->tab[0] == NULL)
		{
			c -= 2;
		}
		if (tokens[i]->type == ARG_CMD)
			c++;
		i++;
	}
	return (i + c);
}
