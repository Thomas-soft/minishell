/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:19:01 by ttofil            #+#    #+#             */
/*   Updated: 2023/05/12 13:36:31 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s || !n)
		return (NULL);
	while (((char *)s)[i] != (char)c && i < n)
		i++;
	if (i == n || ((char *)s)[i] != (char)c)
		return (NULL);
	return ((char *)s + i);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*s;

	s = "TOTOTTE";
	s = ft_memchr(s, 0, 2);
	printf("%s\n", s);
	return (0);
}
*/
