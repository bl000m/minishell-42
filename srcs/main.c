/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:36:33 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/24 11:05:35 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_minish	*data;

	printf("getpid= %d\n", getpid());
	(void) argv;
	check_error(argc);
	data = init_data(envp);
	setting_prompt(data);
	exit_clean(data);
	return (g_status);
}
