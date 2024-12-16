/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:08:21 by ttofil            #+#    #+#             */
/*   Updated: 2023/10/25 19:16:04 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pop_element_list3(t_env *temp)
{
	free(temp->str);
	temp->str = NULL;
	free(temp);
	temp = NULL;
}

static t_env	*pop_element_list2(t_env *before, t_env *after, t_env *env,
		char *s)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
	{
		before = temp;
		temp = temp->next;
		if (temp->next == NULL)
			after = NULL;
		else
			after = temp->next;
		if (strcmp2(s, temp->str, '=') == 0)
		{
			pop_element_list3(temp);
			if (after == NULL)
				before->next = NULL;
			else
				before->next = after;
			temp = before;
		}
		else if (strcmp2(s, before->str, '=') == 0)
			env = pop_front_list(env);
	}
	return (env);
}

t_env	*pop_element_list(t_env *env, char *s)
{
	t_env	*before;
	t_env	*after;

	before = NULL;
	after = NULL;
	if (is_empty(env))
		return (new_list());
	if (env->next == NULL)
	{
		if (strcmp2(s, env->str, '=') == 0)
		{
			free(env->str);
			env->str = NULL;
			free(env);
			env = NULL;
			return (new_list());
		}
	}
	else
	{
		before = env;
		after = env;
		env = pop_element_list2(before, after, env, s);
	}
	return (env);
}

t_env	*pop_front_list(t_env *env)
{
	t_env	*element;

	element = NULL;
	if (is_empty(env))
		return (new_list());
	if (env->next == NULL)
	{
		free(env->str);
		env->str = NULL;
		free(env);
		env = NULL;
		return (new_list());
	}
	element = env->next;
	free(env->str);
	env->str = NULL;
	free(env);
	env = NULL;
	return (element);
}

t_env	*clear_list(t_env *env)
{
	if (is_empty(env))
		return (new_list());
	while (env != NULL)
		env = pop_front_list(env);
	return (new_list());
}
