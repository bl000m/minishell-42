/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:18:27 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 21:32:32 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_ctrlc(int sign, siginfo_t *info, void *context)
// {
// 	static int	pid = 0;

// 	if (!pid)
// 		pid = info->si_pid;
// 	(void) context;
// 	if (sign == SIGINT)
// 	{
// 		if (info->si_pid == pid)
// 		{
// 			write(1, "\n", 1);
// 			// rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 		}
// 	}
// 	if (sign == SIGQUIT)
// 		printf("\b\b  \b\b");
// 	if (!info->si_pid)
// 		exit(128 + sign);
// 	g_status = 128 + sign;
// }

// void	handle_ctrld_exec(int sign)
// {
// 	printf("Quit (core dumped)\n");
// 	g_status = 128 + sign;
// }

// void	handle_ctrlc_exec(int sign)
// {
// 	write(1, "\n", 1);
// 	g_status = 128 + sign;
// }

// void	handle_ctrlc_heredoc(int sign)
// {
// 	write(1, "\n", 1);
// 	g_status = 128 + sign;
// 	close(STDIN_FILENO);
// }
