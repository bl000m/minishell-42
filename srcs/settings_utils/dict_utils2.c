/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:57 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/03/09 16:00:18 by fbelfort         ###   ########.fr       */
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
	if (ptr->value)
		free(ptr->value);
	ptr->value = ft_strdup(newvalue);
	ptr->has_value = 1;
}

void	dict_delone(t_dict **lst, t_dict *node)
{
	t_dict	*ptr;

	if (!ft_memcmp((*lst)->key, node->key, node->key_len))
	{
		ptr = *lst;
		*lst = ptr->next;
		free(ptr->key);
		if (ptr->value)
			free(ptr->value);
		free(ptr);
		return ;
	}
	while ((*lst)->next)
	{
		if (!ft_memcmp((*lst)->next->key, node->key, node->key_len))
		{
			ptr = (*lst)->next;
			(*lst)->next = ptr->next;
			free(ptr->key);
			if (ptr->value)
				free(ptr->value);
			free(ptr);
			return ;
		}
		*lst = (*lst)->next;
	}
}
