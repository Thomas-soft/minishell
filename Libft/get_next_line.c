/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:50:22 by ttofil            #+#    #+#             */
/*   Updated: 2023/06/02 14:12:24 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_str(char *str, char *buf, int *i, int *ret)
{
	char	*temp;

	if (*ret == -1)
		return (NULL);
	buf[*ret] = 0;
	if (*i == 0)
	{
		if (*ret == 0)
			return (NULL);
		str = ft_strdup(buf);
		if (!str)
			return (NULL);
	}
	else
	{
		temp = ft_strjoin(str, buf);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
	}
	*i += *ret;
	return (str);
}

static char	*ft_read(int fd, char *buf)
{
	char	*str;
	int		ret;
	int		i;

	if (buf[ft_strlen_endl(buf)] == '\n')
		return (NULL);
	i = 0;
	if (buf[0])
	{
		str = ft_strdup(buf);
		if (!str)
			return (NULL);
		i++;
	}
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		str = get_str(str, buf, &i, &ret);
		if (!str)
			return (NULL);
		if (str[ft_strlen_endl(str)] == '\n')
			return (str);
	}
	return (str);
}

static char	*read_buf(char *buf)
{
	size_t	i;
	char	*str;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			str = malloc(sizeof(char) * (i + 2));
			if (!str)
				return (NULL);
			break ;
		}
		i++;
	}
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		str[i] = buf[i];
		i++;
	}
	str[i++] = '\n';
	str[i] = 0;
	ft_strlcpy(buf, buf + i, ft_strlen(buf));
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	buf[BUFFER_SIZE + 1];
	size_t		i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = ft_read(fd, buf);
	if (str == NULL)
	{
		if (!buf[0])
			return (NULL);
		str = read_buf(buf);
		if (!str)
			return (NULL);
	}
	else
	{
		i = ft_strlen_endl(str);
		if (str[i] == '\n')
			i++;
		str[i] = 0;
		i = ft_strlen_endl(buf);
		ft_strlcpy(buf, buf + i + 1, ft_strlen(buf));
	}
	return (str);
}
