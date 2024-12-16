/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:37:22 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/04 10:31:24 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty(t_env *env)
{
	if (env == NULL)
		return (1);
	return (0);
}

int	list_length(t_env *env)
{
	int	size;

	size = 0;
	if (is_empty(env))
		return (0);
	while (env != NULL)
	{
		env = env->next;
		size++;
	}
	return (size);
}

void	print_list(t_env *env)
{
	int	i;

	if (is_empty(env))
		return ;
	while (env != NULL)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env->str[i] && env->str[i] != '=')
			ft_putchar_fd(env->str[i++], 1);
		if (env->str[i] == '=')
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('\"', 1);
			i++;
			while (env->str[i])
				ft_putchar_fd(env->str[i++], 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

t_env	*init_env(char **tab_env)
{
	int		i;
	t_env	*env;

	i = 0;
	env = new_list();
	while (tab_env[i])
	{
		env = push_back_list(env, ft_strdup(tab_env[i++]));
		if (env == NULL)
			return (NULL);
	}
	return (env);
}

t_env	*dup_env(t_env *env)
{
	t_env	*new_env;

	new_env = new_list();
	while (env)
	{
		new_env = push_back_list(new_env, ft_strdup(env->str));
		if (new_env == NULL)
			return (NULL);
		env = env->next;
	}
	return (new_env);
}
