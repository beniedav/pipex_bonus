/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:50:53 by badou             #+#    #+#             */
/*   Updated: 2025/06/05 18:54:01 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmd_paths;
	char	***cmds;
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		heredoc;
	char	*limiter;
	int		permission_denied;
}			t_pipex;

// path_utils
char		**get_path_var(char **envp);
char		*find_command_path(char **paths, char *cmd);

// init	struct helper
void		init_input_fds(t_pipex *pipex, char **av);
void		init_input_cmds(t_pipex *pipex, char **av, char **envp);
void		init_cmds(t_pipex *pipex);

// init struct
void		init_struct(t_pipex *pipex, char **av, char **envp);

// processes
void		exec_processes(t_pipex *pipex, char **envp);

// error and free
void		error_and_exit(char *string, int exit);
void		custom_exit(char *string, int exit_code);
void		free_arr(char **arr);
void		close_fds(t_pipex *pipex);
void		cleanup(t_pipex *pipex);
void		safe_close(int fd);

#endif
