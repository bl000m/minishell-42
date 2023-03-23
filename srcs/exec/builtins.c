/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/22 16:13:15 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_minish *data, t_cmd *cmd)
{
	t_dict	*curr;
	size_t	len;
	int		i;
	char	*variable;

	i = 0;
	while (cmd->full_cmd[++i])
	{
		variable = cmd->full_cmd[i];
		len = ft_strlen(variable);
		if (!ft_memcmp(variable, "_", len))
			continue ;
		curr = dict_findvar(data->envp, variable, len);
		if (curr)
			dict_delone(&data->envp, curr);
	}
	g_status = EXIT_SUCCESS;
}

void	env(t_minish *data, t_cmd *cmd)
{
	t_dict	*ptr;

	if (cmd)
	{

		if (cmd->full_cmd[1])
		{
			g_status = EXIT_FAILURE;
			printf("Error: We have to manage the errors\n");
			exit(g_status);
		}
	}
	ptr = data->envp;
	while (ptr)
	{
		if (ptr->has_value)
			printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
	g_status = EXIT_SUCCESS;
	exit(g_status);
}

void	export(t_minish *data, t_cmd *cmd)
{
	t_dict	*ptr;
	size_t	len;
	char	*arg;
	int		i;

	if (!cmd->full_cmd[1])
		print_sorted(data->envp);
	i = 0;
	while (cmd->full_cmd[++i])
	{
		arg = cmd->full_cmd[i];
		len = 0;
		while (arg[len] && arg[len] != '=')
			len++;
		ptr = dict_findvar(data->envp, arg, len);
		if (!ptr)
			dict_addback(&data->envp, dict_newnode(arg));
		if (arg[len] == '=' && ptr)
			set_varvalue(data->envp, ptr->key, ptr->key_len, &arg[len + 1]);
	}
	g_status = EXIT_SUCCESS;
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (cmd->full_cmd[++i])
	{
		if (cmd->full_cmd[i][0] == '-' && cmd->full_cmd[i][1] == 'n')
		{
			j = 2;
			while (cmd->full_cmd[i][j] == 'n')
				j++;
			if (!cmd->full_cmd[i][j] && n == i - 1)
				n = i;
		}
		if (n != i)
			printf("%s", cmd->full_cmd[i]);
		if (cmd->full_cmd[i + 1] && n != i)
			printf(" ");
	}
	if (!n)
		printf("\n");
	g_status = EXIT_SUCCESS;
	exit(g_status);
}
