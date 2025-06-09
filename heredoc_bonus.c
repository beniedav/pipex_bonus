/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:40:39 by badou             #+#    #+#             */
/*   Updated: 2025/06/09 18:09:01 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	fill_heredoc_pipe(t_pipex *pipex, int write_fd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)) == 0
			&& line[ft_strlen(pipex->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-1);
}

void	init_input_fds_heredoc(t_pipex *pipex, int argc, char **av)
{
	int	pipe_fds[2];

	pipex->limiter = av[2];
	pipex->outfile = av[argc - 1];
	if (pipe(pipe_fds) == -1)
		custom_exit("heredoc pipe failed", 1);
	fill_heredoc_pipe(pipex, pipe_fds[1]);
	close(pipe_fds[1]);
	pipex->infile_fd = pipe_fds[0];
	pipex->outfile_fd = open(pipex->outfile, O_CREAT | O_WRONLY | O_APPEND,
			0644);
	if (pipex->outfile_fd < 0)
	{
		perror(pipex->outfile);
		if (errno == EACCES)
			pipex->permission_denied = 1;
	}
}

void	init_input_cmds_heredoc(t_pipex *pipex, int argc, char **av,
		char **envp)
{
	int	i;

	pipex->cmd_count = argc - 4;
	pipex->cmds = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmds)
		custom_exit("malloc cmds failed", 1);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i] = ft_split(av[i + 3], ' ');
		if (!pipex->cmds[i])
		{
			while (--i >= 0)
				free_arr(pipex->cmds[i]);
			free(pipex->cmds);
			custom_exit("ft_split failed", 1);
		}
		i++;
	}
	pipex->cmd_paths = get_path_var(envp);
	if (!pipex->cmd_paths)
		custom_exit("couldn't extract PATH", 1);
}
