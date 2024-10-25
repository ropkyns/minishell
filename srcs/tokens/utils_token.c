/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:36 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 16:00:06 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check si whitespace ou space
 */
bool	is_space(char c)
{
	if ((c && (c >= 9 && c <= 13)) || (c == ' '))
		return (true);
	return (false);
}

/*
 * Check si caractere special (operateur), on return le enum
 */
int	is_special(char *token)
{
	if (token && *token && ft_strlen(token) >= 2)
	{
		if (!ft_strncmp(token, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(token, ">>", 2))
			return (APPEND);
	}
	if (token && *token && ft_strlen(token) >= 1)
	{
		if (!ft_strncmp(token, ">", 1))
			return (OUTPUT);
		if (!ft_strncmp(token, "<", 1))
			return (INPUT);
		if (!ft_strncmp(token, "|", 1))
			return (PIPE);
	}
	return (0);
}

/*
* Ici on calcule la taille de la ligne de commande et le le nombre de quote
(on compte que la 1ere quote car on fait *2 dans la fonction add_cmd_arg)
*/
int	len_cmd(char *command, int *quote)
{
	int	i;

	i = 0;
	*quote = 0;
	while (command[i] && !is_space(command[i]) && !is_special(command + i))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			(*quote)++;
			if (command[i++] == '"')
				while (command[i] && command[i] != '"')
					++i;
			else
				while (command[i] && command[i] != '\'')
					++i;
			if (command[i])
				++i;
		}
		if (command[i] && command[i] != '"' && command[i] != '\''
			&& !is_space(command[i]) && !is_special(command + i))
			++i;
	}
	return (i);
}

/*
* Cette fonction sert a prendre la ligne de commande et de recuperer
ce qu'il y a entre les quotes dans str avec un decalage de -1 pour ne pas
copier les quotes (' et "), sinon sans decalage
*/
void	get_words_to_token(char *command, int len, char *str, int i)
{
	int	j;

	j = 0;
	while (command[i + j] && i < len)
	{
		if (command[i + j] == '\'' && ++j)
		{
			while (command[i + j] != '\'' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else if (command[i + j] == '"' && ++j)
		{
			while (command[i + j] != '"' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else
		{
			str[i] = command[i + j];
			i++;
		}
	}
	str[i] = 0;
}

/*
* On gere les liens de la toute premiere node de la list des tokens
c'est une liste circulaire donc en gros elle va sur elle meme mdr
*/
void	add_first_token(t_structok **token_list, t_structok *new)
{
	(*token_list) = new;
	(*token_list)->prev = *token_list;
	(*token_list)->next = *token_list;
}
