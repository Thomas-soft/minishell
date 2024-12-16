/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:27:06 by ttofil            #+#    #+#             */
/*   Updated: 2023/05/12 13:37:23 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (!s[i] && s[i] != c)
		return (0);
	return ((char *)s + i);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*str;

 	str = "TOTOTTEdsa";
	str = ft_strchr(str, 'E');
	printf("|%s|\n", str);
	return (0);
}
*/
