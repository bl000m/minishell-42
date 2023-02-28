/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: FelipeBelfort <FelipeBelfort@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:57 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/02/28 16:38:00 by FelipeBelfo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief
 * frees the t_dict list. 
 * It verifies for each node if they have a key and a value to be freed
 * and do it if exists.
*/
void    dict_free(t_dict **dict)
{
    t_dict  *ptr;

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

