/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:50:14 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 20:42:06 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Ici on va creer le fameux path, on va calculer la len necessaire a notre
malloc auquel on rajoute +2 (pour le / et pour le '\0')
Ensuite on va copier le path, concatener avec le / et ajouter la cmd
et TADAH on a le path gg
*/
char	*build_path(char *dir, char *cmd)
{
	int		len_path;
	int		cmd_len;
	char	*path_name;

	len_path = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	path_name = malloc(sizeof(char) * (len_path + cmd_len + 2));
	if (!check_allocation(path_name))
		return (NULL);
	ft_strlcpy(path_name, dir, len_path + 1);
	ft_strcat(path_name, "/");
	ft_strcat(path_name, cmd);
	return (path_name);
}

/*
* Envoie dans la fonction build path pour nous creer le chemin
et ensuite verifie si build path a reussi et si le chemin mene
bien a une commande qui est executable
*/
static char	*find_executable(char **path_list, char *cmd_name)
{
	int		i;
	char	*path_name;

	i = 0;
	if (!path_list || !*path_list)
		return (NULL);
	while (path_list[i])
	{
		path_name = build_path(path_list[i], cmd_name);
		if (path_name && access(path_name, X_OK) == 0)
			return (path_name);
		free(path_name);
		i++;
	}
	return (NULL);
}

/*
* Envoie dans la fonction approprie si
il n'y a qu'une seule commande sans pipe ou l'inverse
*/
static void	execute_command(t_cmd *cmd, char *path_name, t_global *glob,
		t_env **env)
{
	if (is_simple_command(glob->token_list))
		execute_simple(cmd, path_name, env);
	else
		execute_piped(cmd, env, glob);
}

/*
* La premiere partie de l'exec, ici on va regarder si il n'y a qu'une
seule commande ou plusieurs avec pipes.

1- > si il n'y en a qu'une on verifie si c'est un builtin,
si c'est le cas on lance le builtin et bravo.

2- > On va envoyer notre nom de cmd dans find executable,
qui va d'abord creer le path avec un strcpy/strcat, pour ensuite
voir si le path est correct et que la cmd existe et est executable.

3- > une seule commande mais pas un builtin, alors dans ce cas
on va l'envoyer dans execute_command -> execute_simple
qui va grosso modo juste execve avec le path qu'on a
cree avant dans un child process pour que cela
ne kill pas notre programme.

4-
Sinon, on va dans execute_piped car il y a plusieurs commandes (et donc pipe)
et la c'est la galere on se revoie la bas ciao (j'aurais du faire pipex)
*/
bool	get_cmd(t_cmd *cmd, t_global **glob, t_env **env)
{
	t_global	*temp;
	char		*path_name;

	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !glob || !*glob)
		return (false);
	temp = *glob;
	if (is_simple_command(temp->token_list))
	{
		if (is_builtins(cmd->cmd_args[0]))
			return (launch_builtin(*glob, cmd));
		path_name = find_executable(temp->path, cmd->cmd_args[0]);
		if (path_name)
		{
			execute_command(cmd, path_name, temp, env);
			return (free(path_name), true);
		}
		else
		{
			(*glob)->exit_value = 127;
			return (printf("bash: command not found: %s\n", cmd->cmd_args[0]),
				false);
		}
	}
	execute_piped(cmd, env, *glob);
	return (true);
}

/*
* Execve dans un child process si il n'y a pas de pipe
(une seule commande en gros)
*/
void	execute_simple(t_cmd *cmd, char *path_name, t_env **env)
{
	pid_t	pid;
	char	**env_array;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		env_array = make_env_tab(*env);
		if (!env_array)
			exit(1);
		if (execve(path_name, cmd->cmd_args, env_array) == -1)
		{
			free(env_array);
			exit(1);
		}
		free(env_array);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
