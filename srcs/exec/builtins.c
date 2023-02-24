/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/02/24 17:18:42 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_minish *data, int fd)
{
	ft_putendl_fd(find_varvalue(data, "PWD", 3), fd);
}

void	unset(t_minish *data, char *variable)
{
	t_dict	*curr;
	t_dict	*next;
	size_t	len;

	len = ft_strlen(variable);
	if (len == 1 && !ft_memcmp(variable, "_", 1))
		return ;
	curr = dict_findvar(data->envp, variable, len);
	if (curr)
	{
		next = curr->next;
		free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
}

void	env(t_minish *data, int fd)
{
	t_dict	*ptr;

	ptr = data->envp;
	while (ptr)
	{
		if (ptr->has_value)
		{
			ft_putstr_fd(ptr->key, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(ptr->value, fd);
		}
		ptr = ptr->next;
	}
}
