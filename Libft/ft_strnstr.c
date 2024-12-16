/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:43 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/12 09:49:31 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& big[i + j] == little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)big + i);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*s;
	char	*f;
	char	*c;
	size_t	i;

	s = "TOTOTTE";
	f = "O";
	i = 2;
	c = ft_strnstr(s, f, i);
	printf("%s\n", c);
	return (0);
}
*/
