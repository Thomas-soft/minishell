/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:20:08 by ttofil            #+#    #+#             */
/*   Updated: 2023/05/12 13:36:16 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char    *dest;
    char    *src;

    dest = malloc(sizeof(dest) * 7);
    src = "Salut";
    dest = ft_memcpy(dest, src, 6);
    // dest = memcpy(dest, src, 6);
    printf("%s\n", dest);
    free(dest);
}
*/
