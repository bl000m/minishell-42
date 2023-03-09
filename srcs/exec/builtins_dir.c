/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: FelipeBelfort <FelipeBelfort@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:40:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/09 00:06:49 by FelipeBelfo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_minish *data)
{
	char	*pwd;

	if (data->cmds->full_cmd[2])
		printf("cd: too many arguments\n");
	else
	{
		pwd = getcwd(NULL, 0);
		if (chdir(data->cmds->full_cmd[1]) != 0)
			printf("cd: %s: No such file or directory\n",
				data->cmds->full_cmd[1]);
		else
		{
			set_varvalue(data->envp, "OLDPWD", 6, pwd);
			free(pwd);
			pwd = getcwd(NULL, 0);
			set_varvalue(data->envp, "PWD", 3, pwd);
		}
		free(pwd);
	}
}

void	pwd(t_minish *data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	exit(0);
}
