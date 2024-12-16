/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:31:19 by ttofil            #+#    #+#             */
/*   Updated: 2023/11/14 16:45:20 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_fdp(t_token **tokens, t_exec *exec)
{
	if (has_pipe(tokens) && (dup2(exec->p_fd[1], STDOUT_FILENO) == -1
			|| close(exec->p_fd[1]) == -1 || close(exec->p_fd[0]) == -1))
		return (ft_perror("fd"));
	if (exec->fd1 && (dup2(exec->fd1, STDIN_FILENO) == -1
			|| close(exec->fd1) == -1))
		return (ft_perror("fd"));
	if (exec->fd2 && (dup2(exec->fd2, STDOUT_FILENO) == -1 || close(exec->fd2)))
		return (ft_perror("fd"));
	return (0);
}

static int	handle_child(t_token **tokens, t_env *env, t_exec *exec,
		t_to_free *to_free)
{
	setup_signal2();
	if (handle_fdp(tokens, exec) == -1)
		return (-1);
	if (exec->res == 1)
	{
		if (ft_strcmp(tokens[0]->tab[0], "echo") == 0)
			ft_echo(tokens[0]->tab + 1);
		else if (ft_strcmp(tokens[0]->tab[0], "pwd") == 0)
			exec->res = ft_pwd();
		else if (ft_strcmp(tokens[0]->tab[0], "export") == 0)
			exec->res = ft_export(tokens[0]->tab + 1, env);
		else if (ft_strcmp(tokens[0]->tab[0], "unset") == 0)
			ft_unset(tokens[0]->tab + 1, env);
		else if (ft_strcmp(tokens[0]->tab[0], "env") == 0)
			ft_env(env);
		else if (execve_cmd(tokens, to_free) == -1)
			return (-1);
		if (exec->res == -1)
			return (-1);
	}
	ft_exit(to_free->tokens, to_free->env, to_free->line);
	exit(0);
	return (0);
}

static int	exec_cmd_custom(t_token **tokens, t_env *env, t_to_free *to_free)
{
	int	res;

	res = 0;
	if (ft_strcmp(tokens[0]->tab[0], "cd") == 0)
		res = ft_cd(tokens[0]->tab + 1, env);
	else if (ft_strcmp(tokens[0]->tab[0], "export") == 0 && tokens[0]->tab[1])
		res = ft_export(tokens[0]->tab + 1, env);
	else if (ft_strcmp(tokens[0]->tab[0], "unset") == 0 && tokens[0]->tab[1])
		ft_unset(tokens[0]->tab + 1, env);
	else if (ft_strcmp(tokens[0]->tab[0], "exit") == 0)
	{
		ft_exit(to_free->tokens, to_free->env, to_free->line);
		exit(0);
	}
	else
		res = 1;
	if (res == -1)
		return (-1);
	return (res);
}

static int	handle_cmd2(t_token **tokens, t_env *env, t_exec *exec,
		t_to_free *to_free)
{
	exec->pid = fork();
	if (exec->pid == -1)
		return (ft_perror("pid"));
	if (exec->pid == 0)
	{
		if (handle_child(tokens, env, exec, to_free) == -1)
			return (-1);
	}
	else
	{
		setup_signal2();
		waitpid(exec->pid, &g_var, 0);
		setup_signal();
		if (exec->fd1 && close(exec->fd1) == -1 && exec->fd2
			&& close(exec->fd2) == -1)
			return (-1);
		if (has_pipe(tokens) && (dup2(exec->p_fd[0], STDIN_FILENO) == -1
				|| close(exec->p_fd[1]) == -1 || close(exec->p_fd[0]) == -1))
			return (ft_perror("dup/fd"));
		if (!has_pipe(tokens) && dup2(1, 0) == -1)
			return (ft_perror("dup"));
	}
	return (0);
}

int	handle_cmd(t_token **tokens, t_env *env, t_to_free *to_free)
{
	t_exec	exec;

	ft_bzero(&exec, sizeof(exec));
	exec.res = exec_cmd_custom(tokens, env, to_free);
	exec.fd1 = handle_redirections_1(tokens, to_free);
	if (exec.fd1 == -1)
	{
		g_var = 1;
		return (0);
	}
	exec.fd2 = handle_redirections_2(tokens);
	if (exec.fd2 == -1)
		return (-1);
	if (has_pipe(tokens) && pipe(exec.p_fd) == -1)
		return (ft_perror("pipe"));
	if (tokens[0] && tokens[0]->type == CMD)
	{
		if (handle_cmd2(tokens, env, &exec, to_free) == -1)
			return (-1);
	}
	return (0);
}
