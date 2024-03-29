/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:57 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/04/01 15:13:37 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	set_varvalue(t_dict *envp, char *variable, size_t len, char *newvalue)
{
	t_dict	*ptr;

	ptr = dict_findvar(envp, variable, len);
	if (!ptr)
		return (0);
	if (ptr->value)
		free(ptr->value);
	ptr->value = ft_strdup(newvalue);
	ptr->has_value = 1;
	return (1);
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
