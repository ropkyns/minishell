/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:19:21 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 14:30:46 by mjameau          ###   ########.fr       */
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
char	*find_executable(char **path_list, char *cmd_name)
{
	int		i;
	char	*path_name;

	i = 0;
	if (!path_list || !*path_list)
		return (NULL);
	if (is_builtins(cmd_name))
		return (path_name = ft_strdup(""));
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
void	process(t_cmd *cmd, char *path_name, t_global *glob, t_env **env)
{
	if (is_simple_command(glob->token_list))
		execute_simple(cmd, path_name, env, glob);
	else
		execute_piped(cmd, env, glob);
}

void	simple_exec_fail_pid(t_global *glob, pid_t pid, t_cmd *cmd)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_nl);
	signal(SIGQUIT, handle_nl);
	waitpid(pid, &glob->exit_value, 0);
	handle_parent_process2(cmd);
	if (WIFEXITED(glob->exit_value))
		glob->exit_value = WEXITSTATUS(glob->exit_value);
}
