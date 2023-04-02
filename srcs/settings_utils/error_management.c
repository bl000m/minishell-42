/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:55:27 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 16:00:09 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error(int argc)
{
	if (argc != 1)
	{
		ft_printf("n. of argument incorrected\n");
		exit(1);
	}
}

/**
 * @brief
 * The function will print the given error message, update
 * the g_status and
 * call exit() if that's the case,
 *if 0 it won't exit otherwise is calls exit(code).
 * @param int exit_code
 * @param char* message -> the message to be printed
 * @param void* a pointer to a variable to fill the message
 * @param int the code to be put in the g_status
*/
void	error_manager(int exit_code, char *message, void *var, int error_code)
{
	g_status = error_code;
	if (message && !var)
		printf("%s", message);
	if (message && var)
		printf(message, var);
	if (exit_code)
		exit(exit_code);
}
