/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:43:22 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/21 16:33:48 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief
 * It will iterate over the array of arrays guven in argument
 * to find it's size then duplicates all the correspondent arrays.
 * It returns an exact copy of the array and has to be freed up at the end.
*/
static char	**dup_envp(char *envp[])
{
	char	**dup;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(dup));
	if (!dup)
		return (NULL);
	i = -1;
	while (envp[++i])
		dup[i] = ft_strdup(envp[i]); // add an error management to free if needed.
	return (dup);
}

t_minish	*init_data(int argc, char *envp[])
{
	t_minish	*data;

	(void) envp;
	data = malloc(sizeof(*data));
	if (!data)
	{
		ft_printf("ERROR ALLOCATING DATA: %s\n", strerror(errno));
		exit(1);
	}
	// data->envp = NULL;
	data->argc = argc;
	data->pipe[1] = 0;
	data->pipe[0] = 0;
	data->n_cmd = 0;
	data->n_tokens = 0;
	data->pos = 0;
	data->file_in = 0;
	data->file_out = 0;
	data->path = NULL;
	data->path_dir = NULL;
	data->commands = NULL;
	data->full_command = NULL;
	data->dir_command = NULL;
	data->tokens = NULL;
	data->envp = dup_envp(envp); // add an error management
	data->child = 0;
	return (data);
}
