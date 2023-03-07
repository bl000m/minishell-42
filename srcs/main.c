/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:36:33 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/07 16:34:04 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* remember to free (and = NULL) full_command*/
int	main(int argc, char *argv[], char *envp[])
{
	t_minish	*data;

	(void) argv;
	check_error(argc);
	data = init_data(envp);
	setting_prompt(data);
	return (0);
}
