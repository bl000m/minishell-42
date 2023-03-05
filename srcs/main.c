/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:36:33 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 12:56:33 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* remember to free (and = NULL) full_command*/
int	main(int argc, char *argv[], char *envp[])
{
	t_minish	*data;

	(void) argv;
	check_error(argc);
	data = malloc(sizeof(*data));
	if (!data)
	{
		ft_printf("ERROR ALLOCATING DATA: %s\n", strerror(errno));
		exit(1);
	}
	setting_prompt(data, envp);
	return (0);
}