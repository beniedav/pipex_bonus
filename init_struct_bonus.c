/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:14:09 by badou             #+#    #+#             */
/*   Updated: 2025/06/05 19:18:49 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	pipex->outfile_fd = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	int	cmd_start = 2;
	int	cmd_end = argc - 2;

	pipex->cmd_count = cmd_end - cmd_start + 1;
	pipex->cmds = malloc(sizeof(char **) * (pipex->cmd_count));
	if (!pipex->cmds)
		custom_exit("malloc cmds failed", 1);
	i = 0;
	while (cmd_start + i <= cmd_end)
	{
		pipex->cmds[i] = ft_split(av[cmd_start + i], ' ');
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
				write(2, pipex->cmds[i][0],
					ft_strlen(pipex->cmds[i][0]));
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

void	init_struct(t_pipex *pipex, char **av, char **envp, int argc)
{
	init_input_fds(pipex, argc, av);
	init_input_cmds(pipex, argc, av, envp);
	init_cmds(pipex);
	return ;
}
