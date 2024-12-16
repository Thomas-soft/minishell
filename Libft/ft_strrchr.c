/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:32:24 by ttofil            #+#    #+#             */
/*   Updated: 2023/05/12 13:37:11 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	while (s[i] != (char)c && i > 0)
		i--;
	if (s[i] != (char)c)
		return (0);
	return ((char *)s + (i));
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*str;

	str = ".TOTOTTE";
	str = ft_strrchr(str, 'T');
	printf("|%s|\n", str);
	return (0);
}
*/
