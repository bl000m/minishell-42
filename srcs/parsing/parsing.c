/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:54:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/24 14:09:17 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_path(t_minish *data)
{
	data->path = find_varvalue(data, "PATH", 4);
	if (!data->path)
		error_manager(4, data, NULL);
	else
		data->path_dir = ft_split(data->path, ':');
}

/**
 * @brief
 * It will look for the variable given in arg and return it's value
 * The comparison is made based on the name of the variable given and
 * the variable stocked on the data->envp and in the length of both
 * @param t_minish *data
 * @param char *variable -> the name of the variable to be searched
 * @param size_t len -> the length of the name of the variable to be searched
 * @return
 * char* -> the value of the variable
 * NULL if it doesn't exist
*/
char	*find_varvalue(t_minish *data, char *variable, size_t len)
{
	t_dict	*ptr;

	ptr = dict_findvar(data->envp, variable, len);
	if (!ptr)
		return (NULL);
	return (ptr->value);
}

char	*find_dir_command(t_minish *data, char *command)
{
	int		i;
	char	*path_dir;
	char	*path_with_command;

	i = 0;
	while (data->path_dir[i])
	{
		path_dir = ft_strjoin(data->path_dir[i], "/");
		path_with_command = ft_strjoin(path_dir, command);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		else if (access(path_with_command, F_OK | X_OK) == 0)
			return (path_with_command);
		free(path_with_command);
		free(path_dir);
		i++;
	}
	return (NULL);
}
