/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:34:00 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/04 09:54:34 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}
