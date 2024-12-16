/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:19:56 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/11 19:06:58 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && i < n - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
    char    *s1;
    char    *s2;

    s1 = "Toto";
    s2 = "aotz";
    printf("%d\n", memcmp(s1, s2, 1));
    printf("%d\n", ft_memcmp(s1, s2, 1));
    return (0);
}
*/
