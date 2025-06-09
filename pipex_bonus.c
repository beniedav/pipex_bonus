/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:54:15 by badou             #+#    #+#             */
/*   Updated: 2025/06/09 18:05:05 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_init(t_pipex *pipex)
{
	if (!pipex)
		return ;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->pipes = NULL;
	pipex->pids = NULL;
	pipex->cmds = NULL;
	pipex->cmd_paths = NULL;
	pipex->cmd_count = 0;
	pipex->limiter = NULL;
	pipex->permission_denied = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		custom_exit("Expected 4 arguments", 1);
	pipex.heredoc = (ft_strncmp(av[1], "here_doc", 9) == 0);
	pipex_init(&pipex);
	init_struct(&pipex, av, envp, ac);
	exec_processes(&pipex, envp);
	return (1);
}
