/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:25:35 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 16:55:05 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d_char(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
		free(tab[j++]);
	free(tab);
}

void	err_free_2d_char(char **tab, int j)
{
	while (j >= 0)
		free(tab[j--]);
	free(tab);
}

void	free_token(t_token **tokens, int tab)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tab)
			free_2d_char(tokens[i]->tab);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	err_free_token(t_token **tokens, int j, int tab)
{
	while (j >= 0)
	{
		if (tab)
			free_2d_char(tokens[j]->tab);
		free(tokens[j]);
		j--;
	}
	free(tokens);
}
