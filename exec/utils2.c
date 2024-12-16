/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:33:42 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/04 10:13:54 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_tab(char **old_tab)
{
	int		i;
	char	**tab;

	i = 0;
	while (old_tab[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (old_tab[i])
	{
		tab[i] = ft_strdup(old_tab[i]);
		if (tab[i] == NULL)
		{
			err_free_2d_char(tab, i - 1);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**get_env(t_env *old_env)
{
	int		i;
	char	**env;

	i = 0;
	env = malloc(sizeof(char *) * (list_length(old_env) + 1));
	if (env == NULL)
		return (NULL);
	while (old_env)
	{
		env[i] = ft_strdup(old_env->str);
		if (env[i] == NULL)
		{
			err_free_2d_char(env, i - 1);
			return (NULL);
		}
		old_env = old_env->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

static void	refresh_pwd2(char *str, char *var, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i])
		str[j++] = var[i++];
	i = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
}

int	refresh_pwd(t_env *env, char *var)
{
	char	*buffer;
	t_env	*temp;

	temp = env;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		return (ft_perror("getcwd"));
	while (temp)
	{
		if (strcmp2(temp->str, var, '=') == 0)
		{
			free(temp->str);
			temp->str = malloc(sizeof(char) * (ft_strlen(var)
						+ ft_strlen(buffer) + 1));
			if (temp->str == NULL)
			{
				free(buffer);
				return (-1);
			}
			refresh_pwd2(temp->str, var, buffer);
		}
		temp = temp->next;
	}
	free(buffer);
	return (0);
}
