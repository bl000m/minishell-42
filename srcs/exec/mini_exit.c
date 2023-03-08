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

/* remember to replace atoi with right ft_atoi*/
void	mini_exit(t_cmd **cmd)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (!(*cmd)->full_cmd[1])
		exit(0);
	if ((*cmd)->full_cmd[2])
		printf("exit: too many arguments\n");
	else
	{
		while ((*cmd)->full_cmd[1][i])
		{
			if ((*cmd)->full_cmd[1][i] < '0' || (*cmd)->full_cmd[1][i] > '9')
			{
				printf("exit: %s: numeric argument required\n", (*cmd)->full_cmd[1]);
				exit(2);
			}
			else if ((*cmd)->full_cmd[1][i] > '0' && (*cmd)->full_cmd[1][i] < '9')
				exit((atoi((*cmd)->full_cmd[1])) % 256);
			i++;
		}
	}
}
