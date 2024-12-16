/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:01:15 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/12 09:50:57 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;

	s = malloc(sizeof(char *) * n);
	if (!s)
		return (NULL);
	ft_memcpy(s, src, n);
	ft_memcpy(dest, s, n);
	free(s);
	return (dest);
}
