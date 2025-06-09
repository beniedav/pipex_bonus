/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:02:27 by badou             #+#    #+#             */
/*   Updated: 2025/06/09 17:05:10 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_and_exit(char *string, int exit_code)
{
	perror(string);
	exit(exit_code);
}

void	custom_exit(char *string, int exit_code)
{
	write(2, string, ft_strlen(string));
	exit(exit_code);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	cleanup(t_pipex *pipex)
{
	int	i;

	safe_close(pipex->infile_fd);
	safe_close(pipex->outfile_fd);
	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->cmd_count - 1)
		{
			safe_close(pipex->pipes[i][0]);
			safe_close(pipex->pipes[i][1]);
			free(pipex->pipes[i]);
			i++;
		}
		free(pipex->pipes);
	}
	i = 0;
	while (pipex->cmds && i < pipex->cmd_count)
		free_arr(pipex->cmds[i++]);
	free(pipex->cmds);
	free_arr(pipex->cmd_paths);
	free(pipex->pids);
}
