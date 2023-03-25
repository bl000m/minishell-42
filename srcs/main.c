/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:36:33 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/25 09:39:58 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_minish	*data;

	// printf("getpid= %d\n", getpid());
	(void) argv;
	check_error(argc);
	data = init_data(envp);
	setting_prompt(data);
	exit_clean(data);
	return (g_status);
}
