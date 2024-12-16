/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:36:45 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/12 15:11:59 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_s;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new_s = malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	i = start;
	while (s[i - start] && i - start < len)
	{
		new_s[i - start] = s[i];
		i++;
	}
	new_s[i - start] = 0;
	return (new_s);
}

/*
#include <stdio.h>
int main(void)
{
	char    *s;
	char    *new_s;

	s = "TOTOTTE";
	new_s = ft_substr(s, 2, 7);
	printf("|%s|\n", new_s);
	free(new_s);
}
*/
