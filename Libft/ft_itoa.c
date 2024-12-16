/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:18:47 by ttofil            #+#    #+#             */
/*   Updated: 2023/04/12 11:18:58 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_len(int nb)
{
	long long int	n;
	size_t			len;

	len = 0;
	n = nb;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

static void	putnbr_chr(char *s, long int nb)
{
	long long int	n;
	size_t			s_len;

	n = nb;
	s_len = ft_strlen(s);
	if (n < 0)
	{
		n = n * -1;
		s[s_len] = '-';
		s_len++;
	}
	if (n >= 10)
	{
		putnbr_chr(s, n / 10);
		putnbr_chr(s, n % 10);
	}
	else
		s[s_len] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*s;

	s = ft_calloc(nb_len(n) + 1, sizeof(char));
	if (!s)
		return (NULL);
	putnbr_chr(s, n);
	s[ft_strlen(s)] = '\0';
	return (s);
}

/*
#include <stdio.h>
int main(void)
{
	char    *s;

	s = ft_itoa(234);
	printf("%s\n", s);
	free(s);
	return (0);
}
*/
