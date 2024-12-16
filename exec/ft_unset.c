/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:21:30 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/25 18:59:01 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **tab, t_env *env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return ;
	if (tab[0])
	{
		while (tab[i])
			env = pop_element_list(env, tab[i++]);
	}
}
