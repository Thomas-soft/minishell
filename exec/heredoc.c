/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:02:41 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/03 16:31:17 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_child2(char *content, char *buf, char *end, int res)
{
	while ((buf[0] == '\n' || ft_strncmp(buf, end, ft_strlen(buf) - 1) != 0)
		&& res != 0)
	{
		content = strjoin2(content, buf);
		if (content == NULL)
			return (NULL);
		if (res == 0)
			break ;
		if (res != 0)
			ft_putstr_fd("heredoc> ", 1);
		res = read(0, buf, 512);
		if (res == -1)
		{
			buf[0] = '\0';
			free(content);
			return (NULL);
		}
		if (res == 0)
			ft_putstr_fd("\n", 1);
		buf[res] = '\0';
	}
	return (content);
}

int	handle_child(char *buf, char *end, int *p_fd)
{
	char	*content;
	int		res;

	res = 1;
	setup_signal2();
	content = malloc(sizeof(char));
	if (content == NULL)
		return (-1);
	content[0] = '\0';
	content = handle_child2(content, buf, end, res);
	if (content == NULL)
		return (-1);
	write(p_fd[1], content, ft_strlen(content));
	if (close(p_fd[1]) == -1)
	{
		free(content);
		return (ft_perror("fd"));
	}
	free(content);
	return (0);
}

int	get_heredoc(char *end, t_to_free *to_free)
{
	int		p_fd[2];
	char	buf[512 + 1];
	int		pid;
	int		g_var;

	if (dup2(1, 0) == -1 || pipe(p_fd) == -1)
		return (ft_perror("dup / pid"));
	buf[0] = '\0';
	pid = fork();
	if (pid == -1)
		return (ft_perror("pid"));
	if (pid == 0)
	{
		handle_child(buf, end, p_fd);
		ft_exit(to_free->tokens, to_free->env, to_free->line);
	}
	else
	{
		setup_signal2();
		waitpid(pid, &g_var, 0);
		setup_signal();
		close(p_fd[1]);
	}
	return (p_fd[0]);
}
