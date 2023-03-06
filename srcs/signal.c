/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:51:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/06 20:01:38 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrlc(int sign)
{
	if (sign == SIGINT)
		// rl_on_new_line();
}

void	handle_ctrld(int sign)
{
	(void)sign;
}
