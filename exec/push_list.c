/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:14:19 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/08 18:08:48 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_list(void)
{
	return (NULL);
}

t_env	*push_back_list(t_env *env, char *s)
{
	t_env	*element;
	t_env	*temp;

	if (s == NULL)
	{
		env = clear_list(env);
		return (NULL);
	}
	element = malloc(sizeof(*element));
	if (element == NULL)
	{
		env = clear_list(env);
		return (NULL);
	}
	element->str = s;
	element->next = NULL;
	if (is_empty(env))
		return (element);
	temp = env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = element;
	return (env);
}

t_env	*push_front_list(t_env *env, char *s)
{
	t_env	*element;

	if (s == NULL)
	{
		env = clear_list(env);
		return (NULL);
	}
	element = malloc(sizeof(*element));
	if (element == NULL)
	{
		env = clear_list(env);
		return (NULL);
	}
	element->str = s;
	if (is_empty(env))
		element->next = NULL;
	else
		element->next = env;
	return (element);
}
