/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:40:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/22 14:02:41 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_minish *data, t_cmd *cmd)
{
	char	*pwd;

	g_status = EXIT_FAILURE;
	if (cmd->full_cmd[2])
		printf("cd: too many arguments\n");
	else
	{
		pwd = getcwd(NULL, 0);
		if (chdir(cmd->full_cmd[1]) != 0)
			printf("cd: %s: No such file or directory\n", cmd->full_cmd[1]);
		else
		{
			set_varvalue(data->envp, "OLDPWD", 6, pwd);
			free(pwd);
			pwd = getcwd(NULL, 0);
			set_varvalue(data->envp, "PWD", 3, pwd);
		}
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
