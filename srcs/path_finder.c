#include "pipex.h"

int	find_i_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

char	**put_bars_and_cmd_on_path(char **path, char **cmd)
{
	int		i;
	char	*aux_1;
	char	*aux_2;

	i = 0;
	while (path[i])
	{
		aux_1 = path[i];
		path[i] = ft_strjoin(path[i], "/");
		aux_2 = path[i];
		path[i] = ft_strjoin(path[i], cmd[0]);
		free(aux_1);
		free(aux_2);
		i++;
	}
	return (path);
}

char	**get_paths(char **cmd, char **env)
{
	int		i_path;
	char	*aux;
	char	**paths_wo_bar;

	i_path = find_i_path(env);
	aux = ft_strtrim(env[i_path], "PATH=");
	paths_wo_bar = ft_split(aux, ':');
	free(aux);
	return (put_bars_and_cmd_on_path(paths_wo_bar, cmd));
}

void	free_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat[i]);
	free(mat);
}

/*Function that will get the correct path to the binary command
 * specified by cmd (the  > 0 entries of this matrix are the corresponding
 * flags if specified). It first gets every path in the PATH env variable,
 * then it adds a / and the exec name to form the correct path (if it
 * exists), and then checks with access(2) wether there is one path
 * that can find the binary, and in that case it returns it.*/
char	*find_exec_path(char **cmd, char **env)
{
	char	**exec_paths;
	char	*path;
	int		i;

	if (access(cmd[0], X_OK | F_OK) == 0)
		return (ft_strdup(cmd[0]));
	exec_paths = get_paths(cmd, env);
	path = NULL;
	i = 0;
	while (exec_paths[i])
	{
		if (access(exec_paths[i], X_OK | F_OK) == 0 && !path)
			path = ft_strdup(exec_paths[i]);
		i++;
	}
	free_matrix(exec_paths);
	if (!path)
		command_not_found_error(cmd);
	return (path);
}
