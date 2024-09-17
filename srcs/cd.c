/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/17 12:23:16 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	update_old_pwd(t_test test)
{
	t_list	*temp;
	char	*check;
	int		len;

	*temp = test->envi;
	check = NULL;
	len = ft_lstsize(temp);
	while (len--)
	{
		if (ft_strncmp(temp->str, "PWD=3", 3) == 0)
			check = temp->str;
		temp = temp->next;
	}
	if (!check)
		export("OLDPWD", &test->envi);
	if (check)
	{
		check = ft_strjoin("OLD", check);
		if (!check)
			return (ERR_MALLOC);
		export(check, test->envi);
	}
	free(test);
}

static void	update_pwd(t_test test, char *args)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_prev_pwd(test);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(args);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (ERR_MALLOC);
	export(pwd, &test->envi);
	free(pwd);
}
int	ft_cd(t_test *test, char **args)
{
	int	ret;

	if (check_args(args) == 2)
	{
		ret = chdir(args[1]);
		if (ret == 0)
			update_pwd(test, args[1]);
		if (ret < 0)
			perror(args[1]);
		return (ret);
	}
	return (FAIL);
}
