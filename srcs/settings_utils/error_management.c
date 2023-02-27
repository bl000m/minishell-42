/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:55:27 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 13:06:39 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_error(int argc)
{
	if (argc != 1)
	{
		ft_printf("n. of argument incorrected\n");
		exit(1);
	}
}

void	error_manager(int error, t_minish *data, t_cmd **cmd)
{
	if (error == 1)
		ft_printf("ERROR CREATING PIPE\n");
	else if (error == 2)
		ft_printf("ERROR CREATING PROCESS\n");
	else if (error == 3)
		ft_printf("command not found. %s\n",
			(*cmd)->full_cmd[0]);
	else if (error == 4)
		ft_printf("ENV PATH not set\n");
	else if (error == 5)
	{
		if (data->file_in)
			close(data->file_in);
		ft_printf("OUTPUT ERROR\n");
	}
	else if (error == 6)
		ft_printf("ERROR in switching fd\n");
	else if (error == 7)
		ft_printf("parse error near '|'\n");
	else if (error == 8)
		ft_printf("syntax error near unexpected token `newline'\n");
	exit_clean(data);
	exit(1);
}
