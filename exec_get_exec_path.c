/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_exec_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:48:38 by fmaurer           #+#    #+#             */
/*   Updated: 2024/12/03 21:23:54 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_path_from_env(char **env);
static char	*join_exec_path_strings(char *path, char *exec);
static void	free_split(char ***split);
static int	ft_initial_strcmp(char *s1, char *s2);

// FIXME: the access check is not working properly. It also succeeds on
// directories with the executable bit set. This is not the desired behaviour.
char	*get_exec_path(t_cmdlst *clst, char **env)
{
	int		i;
	char	**path_split;
	char	*exec_path;

	if (access(clst->cmd, X_OK) == 0)
		return (clst->cmd);
	path_split = get_path_from_env(env);
	i = -1;
	while (path_split[++i])
	{
		exec_path = join_exec_path_strings(path_split[i], clst->cmd);
		if (access(exec_path, X_OK) == 0)
		{
			ft_printf("<< DEBUG >> i really can access X_OK: %s\n", exec_path);
			free_split(&path_split);
			return (exec_path);
		}
		free(exec_path);
	}
	free_split(&path_split);
	return (NULL);
}

char	**get_path_from_env(char **env)
{
	int		i;
	char	**path_split;

	if (!env || !env[0])
		error_exit("empty env");
	i = 0;
	while (!ft_initial_strcmp(env[i], "PATH") && env[i])
		i++;
	if (!env[i])
		error_exit("no PATH found in env");
	path_split = ft_split((env[i] + 5), ':');
	if (!path_split)
		error_exit("malloc in get_path_from_env ft_split failed");
	return (path_split);
}

char	*join_exec_path_strings(char *path, char *exec)
{
	char	*path_slash;
	char	*exec_path;

	path_slash = ft_strjoin(path, "/");
	nullcheck(path_slash, "path_slash malloc failed");
	exec_path = ft_strjoin(path_slash, exec);
	nullcheck(exec_path, "exec_path malloc failed");
	free(path_slash);
	return (exec_path);
}

void	free_split(char ***split)
{
	char	**tmp;

	tmp = *split;
	while (**split)
	{
		free(**split);
		(*split)++;
	}
	free(tmp);
}

int	ft_initial_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}