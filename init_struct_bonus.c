/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:14:09 by badou             #+#    #+#             */
/*   Updated: 2025/06/09 17:53:50 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_input_fds(t_pipex *pipex, int argc, char **av)
{
	pipex->infile = av[1];
	pipex->outfile = av[argc - 1];
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	if (pipex->infile_fd < 0)
	{
		perror(pipex->infile);
		if (errno == EACCES)
			pipex->permission_denied = 1;
	}
	pipex->outfile_fd = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (pipex->outfile_fd < 0)
	{
		perror(pipex->outfile);
		if (errno == EACCES)
			pipex->permission_denied = 1;
	}
}

void	init_input_cmds(t_pipex *pipex, int argc, char **av, char **envp)
{
	int	i;

	pipex->cmd_count = argc - 3;
	pipex->cmds = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmds)
		custom_exit("malloc cmds failed", 1);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i] = ft_split(av[i + 2], ' ');
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

void	init_cmds(t_pipex *pipex)
{
	int		i;
	char	*path;

	i = 0;
	while (i < pipex->cmd_count)
	{
		path = find_command_path(pipex->cmd_paths, pipex->cmds[i][0]);
		if (!path)
		{
			if (pipex->cmds[i][0])
				write(2, pipex->cmds[i][0], ft_strlen(pipex->cmds[i][0]));
			write(2, ": command not found\n", 21);
		}
		else
		{
			free(pipex->cmds[i][0]);
			pipex->cmds[i][0] = path;
		}
		i++;
	}
}

void	allocate_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
		custom_exit("malloc pipes failed", 1);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			custom_exit("malloc pipe pair failed", 1);
		if (pipe(pipex->pipes[i]) == -1)
			custom_exit("pipe creation failed", 1);
		i++;
	}
}

void	init_struct(t_pipex *pipex, char **av, char **envp, int argc)
{
	if (pipex->heredoc)
	{
		init_input_fds_heredoc(pipex, argc, av);
		init_input_cmds_heredoc(pipex, argc, av, envp);
	}
	else
	{
		init_input_fds(pipex, argc, av);
		init_input_cmds(pipex, argc, av, envp);
	}
	init_cmds(pipex);
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		custom_exit("malloc pids failed", 1);
	allocate_pipes(pipex);
}
