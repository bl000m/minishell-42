/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:08:20 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/07 18:32:06 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_exit(t_cmd **cmd)
{
	int	i;
	int	exit_code;

	i = 0;
	printf("exit\n");
	if (!(*cmd)->full_cmd[1])
		exit(0);
	while ((*cmd)->full_cmd[1][i])
	{
		if ((*cmd)->full_cmd[1][i] < '0' || (*cmd)->full_cmd[1][i] > '9')
		{
			printf("exit: %s: numeric argument required\n", (*cmd)->full_cmd[1]);
			exit(2);
		}
	}
	if ((*cmd)->full_cmd[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		cmd = 0;
	}
	else
	{
		exit_code = ft_atoi((*cmd)->full_cmd[1]);
		exit(exit_code%256);
	}
}
