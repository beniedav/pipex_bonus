#include "pipex_bonus.h"

void	setup_pipe_fds(t_pipex *pipex, int i)
{
	int	null_fd;

	if (i == 0)
	{
		if (pipex->infile_fd >= 0)
			dup2(pipex->infile_fd, STDIN_FILENO);
		else
		{
			null_fd = open("/dev/null", O_RDONLY);
			dup2(null_fd, STDIN_FILENO);
			safe_close(null_fd);
		}
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		if (pipex->outfile_fd >= 0)
			dup2(pipex->outfile_fd, STDOUT_FILENO);
		else
		{
			null_fd = open("/dev/null", O_WRONLY);
			dup2(null_fd, STDOUT_FILENO);
			safe_close(null_fd);
		}
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
		i++;
	}

	close_all_pipes(pipex);
	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		i++;
	}
	cleanup(pipex);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}

