/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:40:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/23 12:44:41 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_minish *data, t_cmd *cmd)
{
	char	*pwd;

	if (!cmd->full_cmd[1])
		return ;
	if (cmd->full_cmd[2])
		error_manager(14, data, &cmd);
	else
	{
		if (chdir(cmd->full_cmd[1]) != 0)
		{
			error_manager(13, data, &cmd);
			return ;
		}
		pwd = getcwd(NULL, 0);
		set_varvalue(data->envp, "OLDPWD", 6, pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		set_varvalue(data->envp, "PWD", 3, pwd);
		free(pwd);
		g_status = EXIT_SUCCESS;
	}
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
