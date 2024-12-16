/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:35:18 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/14 16:53:49 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	return_err(char *str)
{
	ft_putendl_fd(str, 2);
	return (0);
}

static int	len_path(char *str, t_env *env)
{
	int		i;
	int		len;
	char	*home;

	i = 0;
	len = 0;
	home = getenv_value("HOME", env);
	if (home == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '~')
		{
			len += ft_strlen(home);
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	free(home);
	return (len);
}

static int	get_path(char *str, t_env *env, char *path)
{
	t_index	i;
	char	*home;

	init_index(&i);
	home = getenv_value("HOME", env);
	if (home == NULL)
		return (-1);
	while (str[i.i])
	{
		if (str[i.i] == '~')
		{
			i.k = 0;
			while (home[i.k])
				path[i.j++] = home[i.k++];
			i.i++;
		}
		else
			path[i.j++] = str[i.i++];
	}
	path[i.j] = '\0';
	free(home);
	return (0);
}

static char	*get(char *str, t_env *env)
{
	int		res;
	char	*path;

	if (ft_strncmp("-", str, ft_strlen(str)) == 0 && str[0] && str[1] == '\0')
	{
		path = getenv_value("OLDPWD", env);
		if (path == NULL)
			return (NULL);
		return (path);
	}
	res = len_path(str, env);
	if (res == -1)
		return (NULL);
	path = malloc(sizeof(char) * (res + 1));
	if (path == NULL)
		return (NULL);
	if (get_path(str, env, path) == -1)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

int	ft_cd(char **tab, t_env *env)
{
	char	*path;

	if (tab[0] == NULL)
		return (0);
	if (tab[1] != NULL)
		return (return_err("minishell: cd: too many arguments"));
	path = get(tab[0], env);
	if (path == NULL)
		return (-1);
	if (access(path, F_OK | X_OK) == 0 && refresh_pwd(env, "OLDPWD=") == -1)
	{
		free(path);
		return (-1);
	}
	if (chdir(path) != 0)
	{
		free(path);
		return (ft_perror(tab[0]));
	}
	free(path);
	if (refresh_pwd(env, "PWD=") == -1)
		return (-1);
	return (0);
}
