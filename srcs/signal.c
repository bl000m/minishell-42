/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: FelipeBelfort <FelipeBelfort@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:51:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/07 21:59:42 by FelipeBelfo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrlc(int sign)
{
	if (sign == SIGINT)
	{
		printf("^C");
		printf("");
		rl_on_new_line();
	}
	if (sign == SIGQUIT)
		printf("SIGQUIT -> %d\n", sign);
	if (sign == EOF)
		printf("EOF -> %d\n", sign);
	// exit(0);
}

void	handle_ctrld(int sign)
{
	(void)sign;
}
