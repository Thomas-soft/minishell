/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:37 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 16:52:08 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size == SIZE_MAX || nmemb == SIZE_MAX)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*
#include <stdio.h>
int	main(void)
{
	int	*tab;
	int	i;

	tab = ft_calloc(10, sizeof(tab));
	i = 0;
	while (i < 10)
	{
		printf("%d ", tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
*/
