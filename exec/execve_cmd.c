/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:38:36 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/08 18:51:58 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execve_cmd(t_token **tokens, t_to_free *to_free)
{
	char	**tab;
	char	**tenv;

	tab = get_tab(tokens[0]->tab);
	tenv = get_env(to_free->env);
	if (tab == NULL)
		return (-1);
	if (tenv == NULL)
	{
		free_2d_char(tab);
		return (-1);
	}
	free_token(to_free->tokens, 1);
	to_free->env = clear_list(to_free->env);
	if (tab[0][0] != '0')
		execve(tab[0], tab, tenv);
	free_2d_char(tab);
	free_2d_char(tenv);
	ft_exit(NULL, NULL, to_free->line);
	exit(1);
	return (0);
}
