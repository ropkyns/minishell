/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/26 16:01:07 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// static int	envsize(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (env)
// 	{
// 		env = env->next;
// 		i++;
// 	}
// 	return (i);
// }

// static void	update_old_pwd(t_global *test)
// {
// 	t_env	*temp;
// 	char	*check;
// 	int		len;

// 	temp = test->env;
// 	check = NULL;
// 	len = envsize(temp);
// 	while (len--)
// 	{
// 		if (ft_strncmp(temp->str, "PWD=", 3) == 0)
// 			check = temp->str;
// 		temp = temp->next;
// 	}
// 	if (!check)
// 		export_value(&test->env, "OLDPWD");
// 	if (check)
// 	{
// 		check = ft_strjoin("OLD", check);
// 		if (!check)
// 			return ;
// 		export_value(&test->env, check);
// 	}
// 	free(test);
// }

// static void	update_pwd(t_global *test, char *args)
// {
// 	char	cwd[PATH_MAX];
// 	char	*pwd;

// 	update_old_pwd(test);
// 	if (getcwd(cwd, PATH_MAX) == NULL)
// 	{
// 		perror(args);
// 		return ;
// 	}
// 	pwd = ft_strjoin("PWD=", cwd);
// 	if (!pwd)
// 	{
// 		printf("malloc error\n");
// 		return ;
// 	}
// 	export_value(&test->env, pwd);
// 	free(pwd);
// }

// int	ft_cd(t_global *test, char *args)
// {
// 	int	ret;

// 	ret = chdir(&args[1]);
// 	if (ret == 0)
// 		update_pwd(test, &args[1]);
// 	if (ret < 0)
// 		perror(&args[1]);
// 	return (ret);
// }
