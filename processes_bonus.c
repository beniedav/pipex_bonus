/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:57:37 by badou             #+#    #+#             */
/*   Updated: 2025/06/09 17:08:14 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	dup_null(int std_fd, int mode)
{
	int	null_fd;

	null_fd = open("/dev/null", mode);
	dup2(null_fd, std_fd);
	safe_close(null_fd);
}

void	setup_pipe_fds(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (pipex->infile_fd >= 0)
			dup2(pipex->infile_fd, STDIN_FILENO);
		else
			dup_null(STDIN_FILENO, O_RDONLY);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		if (pipex->outfile_fd >= 0)
			dup2(pipex->outfile_fd, STDOUT_FILENO);
		else
			dup_null(STDOUT_FILENO, O_WRONLY);
	}
	else
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
}

void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		safe_close(pipex->pipes[i][0]);
		safe_close(pipex->pipes[i][1]);
		i++;
	}
}

static void	child_exec(t_pipex *pipex, int i, char **envp)
{
	setup_pipe_fds(pipex, i);
	close_all_pipes(pipex);
	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	if (pipex->cmds[i][0])
		execve(pipex->cmds[i][0], pipex->cmds[i], envp);
	cleanup(pipex);
	exit(127);
}

void	exec_processes(t_pipex *pipex, char **envp)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] < 0)
			error_and_exit("fork", 1);
		if (pipex->pids[i] == 0)
			child_exec(pipex, i, envp);
		i++;
	}
	close_all_pipes(pipex);
	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	i = 0;
	while (i < pipex->cmd_count)
		waitpid(pipex->pids[i++], &status, 0);
	cleanup(pipex);
	if (pipex->permission_denied == 1)
		exit(1);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(1);
}
