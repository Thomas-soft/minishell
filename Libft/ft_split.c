/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:23:57 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/11 13:56:34 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	string_len(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		len++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (len);
}

static size_t	word_len(char const *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*create_word(char const *s, char c, size_t *i)
{
	char	*tab;
	size_t	j;

	tab = malloc(sizeof(char) * (word_len(s, c, *i) + 1));
	j = 0;
	while (s[*i] && s[*i] != c)
	{
		tab[j] = s[*i];
		*i += 1;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**tab;

	tab = malloc(sizeof(char *) * (string_len(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		tab[j] = create_word(s, c, &i);
		j++;
		while (s[i] && s[i] == c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

/*
#include <stdio.h>
int	main(void)
{
	char	**tab;
    char const  *s = "....toto.le.kiiiiitchi.wael...";
    size_t  i;

    tab = ft_split(s, '.');
    i = 0;
    while (tab[i])
    {
        printf("|%s|\n", tab[i]);
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}
*/
