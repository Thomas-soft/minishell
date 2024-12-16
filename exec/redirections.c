/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:27:58 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/04 11:20:22 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirections_1(t_token **tokens, t_to_free *to_free)
{
	int	i;
	int	fd;

	i = 0;
	if (tokens[i] && tokens[i]->type == CMD)
		i++;
	while (tokens[i] && tokens[i]->tab[0] && is_pr_token(tokens[i]->tab)
		&& ft_strncmp(tokens[i]->tab[0], "<", 1) == 0)
	{
		i++;
		if (ft_strncmp(tokens[i - 1]->tab[0], "<<", 2) == 0)
			fd = get_heredoc(tokens[i]->tab[0], to_free);
		else if (ft_strncmp(tokens[i - 1]->tab[0], "<", 1) == 0)
			fd = open(tokens[i]->tab[0], O_RDONLY);
		if (fd == -1)
			return (ft_perror(tokens[i]->tab[0]));
		if ((tokens[i] && !tokens[i + 1]) || (tokens[i + 1]
				&& ft_strncmp(tokens[i + 1]->tab[0], "<", 1) != 0))
			return (fd);
		if (close(fd) == -1)
			return (ft_perror("fd"));
		if (tokens[i])
			i++;
	}
	return (0);
}

int	handle_redirections_2(t_token **tokens)
{
	int	fd;
	int	i;

	i = 0;
	while ((tokens[i] && tokens[i]->tab[0]) && (!is_pr_token(tokens[i]->tab)
			|| tokens[i]->tab[0][0] == '<'))
		i++;
	while (tokens[i] && tokens[i]->tab[0] && is_pr_token(tokens[i]->tab)
		&& ft_strncmp(tokens[i]->tab[0], ">", 1) == 0)
	{
		i++;
		if (ft_strncmp(tokens[i - 1]->tab[0], ">>", 2) == 0)
			fd = open(tokens[i]->tab[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strncmp(tokens[i - 1]->tab[0], ">", 2) == 0)
			fd = open(tokens[i]->tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
		if ((tokens[i] && !tokens[i + 1]) || (tokens[i + 1]
				&& ft_strncmp(tokens[i + 1]->tab[0], ">", 1) != 0))
			return (fd);
		close(fd);
		if (tokens[i])
			i++;
	}
	return (0);
}
