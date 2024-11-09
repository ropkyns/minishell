/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/09 18:04:25 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	*after_dollar(char *line, size_t *i, t_env *env, t_global *glob)
// {
// 	char	*new_line;
// 	char	*dollar;
// 	size_t	j;

// 	new_line = NULL;
// 	if (line[(*i)] == '?')
// 	{
// 		new_line = ft_strncpy(ft_calloc((*i + 1), sizeof(char)), line, (*i)
// 				- 1);
// 		new_line = ft_strjoin(new_line, ft_itoa(glob->exit_value));
// 		new_line = ft_strjoin(new_line, line + (*i) + 1);
// 		free(line);
// 		line = ft_strdup(new_line);
// 		free(new_line);
// 	}
// 	else
// 	{
// 		j = (*i);
// 		if (ft_isdigit(line[j]))
// 			while (ft_isdigit(line[j]))
// 				j++;
// 		else if (ft_isalpha(line[j]))
// 			while (ft_isalnum(line[j]) && line[j])
// 				j++;
// 		else
// 			return (line);
// 		dollar = ft_strncpy(ft_calloc(j - (*i) + 1, sizeof(char)), line + (*i),
// 				j - (*i));
// 		new_line = ft_strncpy(ft_calloc((*i), sizeof(char)), line, (*i) - 1);
// 		dollar = search_env(dollar, env);
// 		new_line = ft_strjoin(new_line, dollar);
// 		(*i) = j;
// 		new_line = ft_strjoin(new_line, line + (*i));
// 		free(line);
// 		line = ft_strdup(new_line);
// 		free(new_line);
// 		free(dollar);
// 	}
// 	return (line);
// }

static char	*handle_exit_status(char *line, size_t *i, t_global *glob)
{
	char	*new_line;
	char	*exit_value_str;
	char	*temp;

	new_line = ft_strncpy(ft_calloc((*i + 1), sizeof(char)), line, (*i) - 1);
	exit_value_str = ft_itoa(glob->exit_value);
	temp = new_line;
	new_line = ft_strjoin(new_line, exit_value_str);
	free(temp);
	free(exit_value_str);
	temp = new_line;
	new_line = ft_strjoin(new_line, line + (*i) + 1);
	free(temp);
	free(line);
	return (new_line);
}

static size_t	find_end_of_var(char *line, size_t i)
{
	if (ft_isdigit(line[i]))
		while (ft_isdigit(line[i]))
			i++;
	else if (ft_isalpha(line[i]))
		while (ft_isalnum(line[i]) && line[i])
			i++;
	return (i);
}

static char	*replace_var_with_env(char *line, size_t *i, size_t j, t_env *env)
{
	char	*new_line;
	char	*dollar;
	char	*temp;
	char	*env_value;

	dollar = ft_strncpy(ft_calloc(j - (*i) + 1, sizeof(char)), line + (*i), j
			- (*i));
	temp = new_line = ft_strncpy(ft_calloc((*i), sizeof(char)), line, (*i) - 1);
	env_value = search_env(dollar, env);
	temp = new_line;
	new_line = ft_strjoin(new_line, env_value);
	free(temp);
	*i = j;
	temp = new_line;
	new_line = ft_strjoin(new_line, line + (*i));
	free(temp);
	free(line);
	free(env_value);
	return (new_line);
}

char	*after_dollar(char *line, size_t *i, t_env *env, t_global *glob)
{
	size_t	j;

	if (line[(*i)] == '?')
		return (handle_exit_status(line, i, glob));
	j = find_end_of_var(line, *i);
	if (j == *i)
		return (line);
	return (replace_var_with_env(line, i, j, env));
}

bool	replace_dollar(char **line, t_env *env, t_global *glob)
{
	size_t	i;
	bool	single_quote;
	bool	double_quote;

	i = -1;
	single_quote = false;
	double_quote = false;
	while ((*line)[++i])
	{
		check_quotes(&single_quote, &double_quote, NULL, (*line)[i]);
		if ((*line)[i] == '$' && (*line)[i + 1] && !double_quote)
		{
			i++;
			(*line) = after_dollar((*line), &i, env, glob);
			if (!(*line))
				return (false);
		}
	}
	return (true);
}
