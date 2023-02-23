/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:54:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/23 12:25:29 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_environment(t_minish *data, char *envp[])
{
	data->path = searching_path(envp);
	if (!data->path)
		error_manager(4, data);
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

	ptr = data->envp;
	while (ptr)
	{
		if (ptr->key_len == len && !ft_strncmp(ptr->key, variable, len))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

char	*searching_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] != NULL)
		return (envp[i] + 5);
	else
		return (NULL);
}

char	*find_dir_command(t_minish *data)
{
	int		i;
	char	*path_dir;
	char	*path_with_command;

	i = 0;
	while (data->path_dir[i])
	{
		path_dir = ft_strjoin(data->path_dir[i], "/");
		path_with_command = ft_strjoin(path_dir, data->commands[0]);
		if (access(data->commands[0], F_OK | X_OK) == 0)
			return (data->commands[0]);
		else if (access(path_with_command, F_OK | X_OK) == 0)
			return (path_with_command);
		free(path_with_command);
		free(path_dir);
		i++;
	}
	return (NULL);
}

void	matching_commands_with_right_path(t_minish *data, char *argv[], int pos)
{
	data->commands = ft_split(argv[pos], ' ');
	data->dir_command = find_dir_command(data);
	if (!data->dir_command)
		error_manager(3, data);
}
