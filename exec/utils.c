/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:28:50 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/25 19:21:24 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strcmp2(const char *s1, const char *s2, int c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != (char)c)
		i++;
	if ((!s1[i] && !s2[i]) || (!s1[i] && s2[i] == (char)c) || (s1[i] && s2[i]
			&& s1[i] == s2[i] && s1[i] == (char)c))
		return (0);
	return (1);
}

size_t	ft_strlen_endl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static void	strjoin3(char *line, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		line[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j] && s2[j] != '\n')
	{
		line[i] = s2[j];
		i++;
		j++;
	}
	if (s2[j] && s2[j] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
}

char	*strjoin2(char *s1, char *s2)
{
	char	*line;
	int		len;

	len = ft_strlen_endl(s2);
	if (s2[len] && s2[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (ft_strlen(s1) + len + 1));
	if (line == NULL)
	{
		free(s1);
		return (NULL);
	}
	strjoin3(line, s1, s2);
	return (line);
}

int	ft_perror(char *s)
{
	perror(s);
	return (-1);
}
