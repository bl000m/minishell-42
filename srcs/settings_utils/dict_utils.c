/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:42:04 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/03/23 14:41:42 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * It will allocate the memory to create a t_dict node then it will
 * put a copy of the string given in param untill the first '=' and put it
 * in the node->key with the correspondent length in node->key_len
 * and copy the string after the '=' to put in the node->value.
*/
t_dict	*dict_newnode(char *str)
{
	t_dict	*node;
	size_t	i;

	i = 0;
	node = ft_calloc(1, sizeof(t_dict));
	if (!node)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	node->key = ft_substr(str, 0, i);
	node->key_len = ft_strlen(node->key);
	node->has_value = 1;
	if (str[i] == '=')
		node->value = ft_strdup(str + i + 1);
	if (!str[i])
	{
		node->has_value = 0;
		node->value = ft_strdup(str + i);
	}
	node->next = NULL;
	return (node);
}

/**
 * @brief
 * It will add the given node at the end of the given list.
*/
void	dict_addback(t_dict **dict, t_dict *new)
{
	t_dict	*ptr;

	if (dict == NULL)
		return ;
	if (*dict == NULL)
	{
		*dict = new;
		return ;
	}
	ptr = *dict;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

/**
 * @brief
 * It returns the size of the dict list.
*/
size_t	dict_size(t_dict *dict)
{
	size_t	count;
	t_dict	*ptr;

	count = 0;
	ptr = dict;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

/**
 * @brief
 * It will look for the variable given in arg
 * and return the matching node of the list
 * The comparison is made based on the name of the variable given and
 * the variable stocked on the envp and in the length of both
 * @param t_dict *envp  -> the linked list with the variables
 * @param char *variable -> the name of the variable to be searched
 * @param size_t len -> the length of the name of the variable to be searched
 * @return
 * t_dict -> the matching node
 * NULL if it doesn't exist
*/
t_dict	*dict_findvar(t_dict *envp, char *variable, size_t len)
{
	t_dict	*ptr;

	ptr = envp;
	while (ptr)
	{
		if (ptr->key_len == len && !ft_strncmp(ptr->key, variable, len))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/**
 * @brief
 * Takes a t_dict list in argument and returns a
 * duplicated copy of the
 * list.
*/
t_dict	*dict_duplst(t_dict *dict)
{
	t_dict	*dup;
	t_dict	*tmp;

	dup = NULL;
	while (dict)
	{
		tmp = ft_calloc(1, sizeof(t_dict));
		if (!tmp)
		{
			dict_free(&dup);
			return (NULL);
		}
		tmp->has_value = dict->has_value;
		tmp->key_len = dict->key_len;
		tmp->next = NULL;
		tmp->key = ft_strdup(dict->key);
		tmp->value = ft_strdup(dict->value);
		dict_addback(&dup, tmp);
		dict = dict->next;
	}
	return (dup);
}
