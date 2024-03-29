/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:49:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/03 10:14:00 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minish	*init_data(char *envp[])
{
	t_minish	*data;

	data = malloc(sizeof(*data));
	if (!data)
		hard_exit(NULL, NULL, NULL);
	data->n_cmd = 0;
	data->n_tokens = 0;
	data->btw_double_quotes = 0;
	data->btw_simple_quotes = 0;
	data->start = 0;
	data->end = 0;
	init_cmd(data);
	init_ptrs(data, envp);
	return (data);
}

void	update_envp(t_minish *data, t_dict *envp)
{
	int		lvl;
	t_dict	*ptr;

	if (!set_varvalue(envp, "SHELL", 5, "minishell"))
		hard_exit(data, NULL, NULL);
	ptr = dict_findvar(envp, "SHLVL", 5);
	lvl = ft_atoi(ptr->value) + 1;
	free(ptr->value);
	ptr->value = ft_itoa(lvl);
}
