/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:26:35 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/04 10:22:00 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

static int	print_sorted_list(t_env *env)
{
	t_env	*new_env;
	t_env	*begin;

	new_env = dup_env(env);
	if (new_env == NULL)
		return (-1);
	begin = new_env;
	while (new_env->next)
	{
		if (ft_strcmp(new_env->str, new_env->next->str) > 0)
		{
			swap(&new_env->str, &new_env->next->str);
			new_env = begin;
		}
		else
			new_env = new_env->next;
	}
	print_list(begin);
	begin = clear_list(begin);
	return (0);
}

static int	verify(char **tab, int i)
{
	int	j;

	j = 0;
	if (tab[i] && tab[i][0] && (!ft_isalpha(tab[i][0]) && tab[i][0] != '_'))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(tab[i], 2);
		ft_putendl_fd("not a valid identifier", 2);
		return (1);
	}
	while (tab[i] && tab[i][j] && (ft_isalpha(tab[i][j]) || tab[i][j] == '_'
			|| ft_isalnum(tab[i][j]) || tab[i][j] == '\''
			|| tab[i][j] == '\"') && tab[i][j] != '=')
		j++;
	if (tab[i][j] && tab[i][j] != '=')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(tab[i], 2);
		ft_putendl_fd("not a valid identifier", 2);
		return (1);
	}
	return (0);
}

int	add_var(char **tab, t_env *env)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (verify(tab, i) == 1)
			return (0);
		env = pop_element_list(env, tab[i]);
		env = push_back_list(env, ft_strdup(tab[i]));
		if (env == NULL)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_export(char **tab, t_env *env)
{
	if (env == NULL)
		return (0);
	if (tab[0])
	{
		if (add_var(tab, env) == -1)
			return (-1);
	}
	else
	{
		if (print_sorted_list(env) == -1)
			return (-1);
	}
	return (0);
}
