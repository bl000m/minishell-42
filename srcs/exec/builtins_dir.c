/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:40:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/01 11:40:34 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_minish *data, char *path)
{
	char	*pwd;

	if (strchr(path, ' '))
		ft_putendl_fd("cd: too many arguments", 1);
	pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
		ft_putendl_fd("cd: HOME: No such file or directory", 1);
	else
	{
		set_varvalue(data->envp, "OLDPWD", 6, pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		set_varvalue(data->envp, "PWD", 3, pwd);
	}
	free(pwd);
}

void	pwd(t_minish *data, int fd)
{
	ft_putendl_fd(find_varvalue(data, "PWD", 3), fd);
}
