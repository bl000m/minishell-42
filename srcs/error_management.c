/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:55:27 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/24 15:20:17 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_error(int argc)
{
	if (argc < 5)
	{
		ft_printf("n. of argument incorrected\n");
		exit(1);
	}
}

void	error_manager(int error, t_pipe *data)
{
	if (error == 1)
		ft_printf("ERROR CREATING PIPE: %s\n", strerror(errno));
	else if (error == 2)
		ft_printf("ERROR CREATING PROCESS: %s\n", strerror(errno));
	else if (error == 3)
		ft_printf("command not found: %s. %s\n",
			data->commands[0], strerror(errno));
	else if (error == 4)
		ft_printf("ENV PATH not set: %s\n", strerror(errno));
	else if (error == 5)
	{
		if (data->file_in)
			close(data->file_in);
		ft_printf("OUTPUT ERROR: %s\n", strerror(errno));
	}
	else if (error == 6)
		ft_printf("ERROR in switching fd: %s\n", strerror(errno));
	exit_clean(data);
	exit(1);
}
