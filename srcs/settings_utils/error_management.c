/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:55:27 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/09 16:22:45 by mpagani          ###   ########.fr       */
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
	(void)data;
	if (error == 1)
		ft_printf("ERROR CREATING PIPE\n");
	else if (error == 2)
	{
		g_status = EXIT_FAILURE;
		ft_printf("ERROR CREATING PROCESS\n");
	}
	else if (error == 3)
	{
		ft_printf("command not found. %s\n",
			(*cmd)->full_cmd[0]);
		g_status = 127;
	}
	else if (error == 12)
	{
		ft_printf("command found but not executable. %s\n",
			(*cmd)->full_cmd[0]);
		g_status = 126;
	}
	else if (error == 4)
		ft_printf("ENV PATH not set\n");
	else if (error == 5)
	{
		if ((*cmd)->file_in)
			close((*cmd)->file_in);
		ft_printf("OUTPUT ERROR\n", strerror(errno));
	}
	else if (error == 6)
		ft_printf("ERROR in switching OUTPUT for %s fd\n", (*cmd)->full_cmd[0]);
	else if (error == 7)
		ft_printf("parse error near '|'\n");
	else if (error == 8)
		ft_printf("syntax error near unexpected token `newline'\n");
	else if (error == 9)
		ft_printf("INPUT ERROR: %s\n", strerror(errno));
	else if (error == 10)
		ft_printf("ERROR in switching INPUT for %s fd\n", (*cmd)->full_cmd[0]);
	else if (error == 11)
		ft_printf("syntax error near unexpected token `newline'\n", (*cmd)->full_cmd[0]);
	exit_clean(data);
	exit(g_status);
}
