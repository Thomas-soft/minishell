/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:28:30 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 15:24:31 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getenv_value(char *s, t_env *env)
{
	int		i;
	char	*value;

	i = 0;
	while (env)
	{
		if (strcmp2(s, env->str, '=') == 0)
		{
			while (env->str[i] && env->str[i] != '=')
				i++;
			i++;
			if (!env->str[i])
				break ;
			value = ft_strdup(env->str + i);
			if (value == NULL)
				return (NULL);
			return (value);
		}
		env = env->next;
	}
	value = malloc(sizeof(char));
	if (value == NULL)
		return (NULL);
	value[0] = '\0';
	return (value);
}

size_t	ft_nblen(int nb)
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

void	ft_putnbr_chr(char *tab, int *j, long int nb)
{
	long long int	n;

	n = nb;
	if (n < 0)
	{
		n = n * -1;
		tab[*j] = '-';
		*j += 1;
	}
	if (n >= 10)
	{
		ft_putnbr_chr(tab, j, n / 10);
		ft_putnbr_chr(tab, j, n % 10);
	}
	else
	{
		tab[*j] = n + '0';
		*j += 1;
	}
}

int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}
