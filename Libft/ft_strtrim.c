/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:32:55 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/15 11:40:28 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_charset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*s;

	start = 0;
	while (s1[start] && is_charset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_charset(s1[end - 1], set))
		end--;
	s = malloc(sizeof(char) * (end - start + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (start < end)
		s[i++] = s1[start++];
	s[i] = 0;
	return (s);
}

/*
static size_t	is_set(char const *s1, char const *set, size_t j)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1[j] == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	len_without_set(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[i])
	{
		if (!is_set(s1, set, i))
			len++;
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!s1)
		return (NULL);
	s = malloc(sizeof(char) * (len_without_set(s1, set) + 1));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (!is_set(s1, set, i))
		{
			s[j] = s1[i];
			j++;
		}
		i++;
	}
	s[j] = 0;
	return (s);
}
*/

/*
#include <stdio.h>
int main(void)
{
    char    *s;
    char const  *s1 = " . dsa .wds ad  .";
    char const  *sep = ". ";

    s = ft_strtrim(s1, sep);
    printf("|%s|\n", s);
    free(s);
    return (0);
}
*/
