/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/01 13:12:56 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Pour le $, si $? alors on va chercher l'exit value
sinon on va chercher la value (ex echo $PWD - > truc/truc/minishell)
*/
char	*search_env(char *value, t_env *env)
{
	while (env->next)
	{
		if (ft_strcmp(value, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return ("\0");
}

char	*after_dollar(char *line, size_t *i, t_env *env, t_global *glob)
{
	char	*new_line;
	char	*dollar;
	size_t	j;

	new_line = NULL;
	if (line[(*i)] == '?')
	{
		new_line = ft_strncpy(malloc(*i + 1), line, (*i));
		new_line = ft_strjoin(new_line, ft_itoa(glob->exit_value));
		new_line = ft_strjoin(new_line, line + (*i) + 1);
		free(line);
		line = ft_strdup(new_line);
		free(new_line);
	}
	else
	{
		j = (*i);
		if (ft_isdigit(line[j]))
			while (ft_isdigit(line[j]))
				j++;
		else if (ft_isalpha(line[j]))
			while (ft_isalnum(line[j]) && line[j])
				j++;
		else
			return (line);
		dollar = ft_calloc(j - (*i) + 1, sizeof(char));
		if (!dollar)
			return (NULL);
		dollar = ft_strncpy(dollar, line + (*i), j - (*i));
		new_line = ft_calloc((*i), sizeof(char));
		new_line = ft_strncpy(new_line, line, (*i) - 1);
		// printf("%s|\n", line);
		// printf("%c\n", line[(*i)]);
		// printf("%s|\n", new_line);
		new_line = ft_strjoin(new_line, search_env(dollar, env));
		(*i) = j;
		new_line = ft_strjoin(new_line, line + (*i));
		free(line);
		line = ft_strdup(new_line);
		free(new_line);
		free(dollar);
	}
	return (line);
}

bool	replace_dollar(char *line, t_env *env, t_global *glob)
{
	size_t	i;
	bool	single_quote;
	bool	double_quote;

	i = -1;
	single_quote = false;
	double_quote = false;
	while (line[++i])
	{
		check_quotes(&single_quote, &double_quote, NULL, line[i]);
		if (line[i] == '$' && line[i + 1] && !single_quote)
		{
			i++;
			line = after_dollar(line, &i, env, glob);
			if (!line)
				return (false);
		}
	}
	return (true);
}
