/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:01:14 by badou             #+#    #+#             */
/*   Updated: 2025/06/05 19:01:28 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_path_var(char **envp)
{
	char	*unsplit_path;
	char	**split_path;
	int		i;

	unsplit_path = NULL;
	split_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			unsplit_path = (envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!unsplit_path)
		return (NULL);
	split_path = ft_split(unsplit_path, ':');
	return (split_path);
}

char	*find_command_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (!cmd)
		return (NULL);
	if (cmd[0] == '\0')
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		if (!full_path)
			return (NULL);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
