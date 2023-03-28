/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:57 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/03/22 14:02:25 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * frees the t_dict list.
 * It verifies for each node if they have a key and a value to be freed
 * and do it if exists.
*/
void	dict_free(t_dict **dict)
{
	t_dict	*ptr;

	if (!dict)
		return ;
	while (*dict)
	{
		// printf("key => |%s|   value => |%s|\n", (*dict)->key, (*dict)->value);
		ptr = (*dict)->next;
		if ((*dict)->key)
			free((*dict)->key);
		if ((*dict)->value)
			free((*dict)->value);
		free(*dict);
		*dict = ptr;
	}
	dict = NULL;
}

void	set_varvalue(t_dict *envp, char *variable, size_t len, char *newvalue)
{
	t_dict	*ptr;

	ptr = dict_findvar(envp, variable, len);
	if (!ptr)
		return ;
	if (ptr->value)
		free(ptr->value);
	ptr->value = ft_strdup(newvalue);
	ptr->has_value = 1;
}

void	dict_delone(t_dict **lst, t_dict *node)
{
	t_dict	*ptr;

	ptr = *lst;

	if (ptr == node)
		*lst = node->next;
	else
	{
		while (ptr && ptr != node)
		{
			if (ptr->next == node)
			{
				ptr->next = node->next;
				break ;
			}
			ptr = ptr->next;
		}
	}
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
	node = NULL;
}
