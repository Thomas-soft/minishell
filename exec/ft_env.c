/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:11:43 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/04 10:21:39 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env)
{
	t_env	*temp;

	if (env == NULL)
		return ;
	temp = env;
	while (temp)
	{
		ft_putendl_fd(temp->str, 1);
		temp = temp->next;
	}
}
