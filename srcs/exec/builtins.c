/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: FelipeBelfort <FelipeBelfort@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/02/28 16:38:04 by FelipeBelfo      ###   ########.fr       */
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

void	export(t_minish *data, int fd, char *param)
{
	t_dict	*ptr;
	size_t	len;

	if (!param)
		print_sorted(data->envp, fd);
	else
	{
		len = 0;
		while (param[len] && param[len] != '=')
			len++;
		ptr = dict_findvar(data->envp, param, len);
		if (!ptr)
			dict_addback(&data->envp, dict_newnode(param));
		if (param[len] == '=' && ptr)
		{
			free(ptr->value);
			ptr->value = ft_strdup(&param[len + 1]);
		}
	}
}
