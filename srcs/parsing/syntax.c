/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:59:38 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/18 12:06:54 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Pour le $, si $? alors on va chercher l'exit value
sinon on va chercher la value (ex echo $PWD - > truc/truc/minishell)
*/
char *search_env(const char *key, t_env *env) 
{
	 while (env)
 { 
  if (strcmp(key, env->name) == 0) 
  { 
	char *value = strdup(env->value); 
	printf("Retrieved value from environment: %s\n", value); 
	return value;
	} 
	env = env->next; 
	} 
	return strdup(""); // Return empty string if variable not found
}

char *get_elem_env(t_env *env, const char *key)
{
    while (env)
    {
        printf("Searching in environment: %s=%s\n", env->name, env->value); // Debug statement
        if (strcmp(key, env->name) == 0)
        {
            char *value = strdup(env->value);
            printf("Retrieved value from environment: %s\n", value); // Debug statement
            return value;
        }
        env = env->next;
    }
    return strdup(""); // Return empty string if variable not found
}


/*
* Fonction qui va appeler toutes nos petites fonctions "specialises"
pour les erreurs de syntaxe, en fonction de l'erreur on affiche le mssg
approprie.
*/
bool	check_syntax(t_global *glob, t_structok **token_list)
{
	if (is_first_pipe(token_list, glob))
		return (print_error_syntax("|"), false);
	else if (is_last_pipe(token_list, glob))
		return (print_error_syntax("|"), false);
	else if (is_op_before_pipe(token_list, glob))
		return (print_error_syntax("|"), false);
	else if (is_op_after_op(token_list, glob))
		return (false);
	else if (is_last_op(token_list, glob))
		return (
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2),
			false);
	else if (is_invalid(token_list, glob))
		return (false);
	else
		return (true);
}
