/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:40:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/03 17:29:35 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* builtin to be exec in child process: */
void	mini_env(t_minish *data, t_cmd *cmd)
{
	t_dict	*ptr;

	if (cmd && cmd->full_cmd[1])
	{
		error_manager(EXIT_FAILURE, EC_ENVARG, NULL, EXIT_FAILURE);
		return ;
	}
	ptr = data->envp;
	while (ptr)
	{
		if (ptr->has_value && ft_memcmp(ptr->key, "SHLVL", 6))
			printf("%s=%s\n", ptr->key, ptr->value);
		else if (ptr->has_value)
		{
			if (ft_atoi(ptr->value) <= 0)
				printf("%s=0\n", ptr->key);
			else
				printf("%s=%s\n", ptr->key, ptr->value);
		}
		ptr = ptr->next;
	}
	g_status = EXIT_SUCCESS;
	exit(g_status);
}

void	mini_export(t_minish *data, t_cmd *cmd)
{
	int	i;

	g_status = EXIT_SUCCESS;
	if (!cmd->full_cmd[1])
		print_sorted(data->envp);
	i = 0;
	while (cmd->full_cmd[++i])
		export_aux(data, cmd->full_cmd[i]);
	exit(g_status);
}

void	mini_echo(t_cmd *cmd)
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

void	mini_pwd(t_minish *data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_status = EXIT_SUCCESS;
	exit(g_status);
}
