/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:51:46 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/08 18:57:22 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_token **tokens, t_env *env, char *line)
{
	if (tokens != NULL)
		free_token(tokens, 1);
	if (env != NULL)
		env = clear_list(env);
	free(line);
	clear_history();
}
