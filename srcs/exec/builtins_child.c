/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:40:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/23 13:59:50 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* builtin to be exec in child process: */
void	env(t_minish *data, t_cmd *cmd)
{
	t_dict	*ptr;

	if (cmd && cmd->full_cmd[1])
	{
		error_manager(15, data, &cmd);
		return ;
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

void	pwd(t_minish *data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_status = EXIT_SUCCESS;
	exit(g_status);
}