/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:12:55 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/24 20:01:35 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n(char *arg)
{
	if (arg == NULL)
		return (0);
	if (ft_strlen(arg) == 2 && !ft_strncmp(arg, "-n", 2))
		return (1);
	return (0);
}

void	ft_echo(char **tab)
{
	int	i;

	i = 0;
	if (tab[0])
	{
		if (tab[0][0] == '-')
			i = 1;
	}
	while (tab && tab[i])
	{
		ft_putstr_fd(tab[i++], 1);
		if (tab[i])
			ft_putchar_fd(' ', 1);
	}
	if (tab[0])
	{
		if (!is_n(tab[0]))
			ft_putchar_fd('\n', 1);
	}
}
