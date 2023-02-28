/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:03:25 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 13:03:38 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_path_dir(t_minish *data)
{
	int	i;

	i = 0;
	if (data->path_dir)
	{
		while (data->path_dir[i])
		{
			free(data->path_dir[i]);
			data->path_dir[i] = NULL;
			i++;
		}
		free(data->path_dir);
		data->path_dir = NULL;
	}
}
void	free_env_table(t_minish *data)
{
	int	i;

	i = 0;
	if (data->env_table)
	{
		while (data->env_table[i])
		{
			free(data->env_table[i]);
			data->env_table[i] = NULL;
			i++;
		}
		free(data->env_table);
		data->env_table = NULL;
	}
}

void	free_tokens(t_minish *data)
{
	int	i;

	i = 0;
	if (data->tokens)
	{
		while (data->tokens[i])
		{
			free(data->tokens[i]);
			i++;
		}
		free(data->tokens);
	}
}

void	exit_clean(t_minish *data)
{
	free_tokens(data);
	free_env_table(data);
	free_path_dir(data);
	if (data->pipe[0])
		close(data->pipe[0]);
	if (data->pipe[1])
		close(data->pipe[1]);
	if (data->file_in)
		close(data->file_in);
	if (data->file_out)
		close(data->file_out);
	free(data);
}
