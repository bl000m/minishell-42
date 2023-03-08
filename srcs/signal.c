/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:51:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/08 18:05:26 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrlc(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sign == SIGQUIT)
	{
		printf("\b\b  \b\b");
	}
	g_status = 128 + sign;
}

void	handle_ctrld_exec(int signum)
{
	printf("Quit (core dumped)\n");
	g_status = 128 + signum;
	exit(g_status);
}

void	handle_ctrlc_exec(int signum)
{
	write(1, "\n", 1);
	g_status = 128 + signum;
	exit(g_status);
}

void	handle_ctrlc_heredoc(int signum)
{
	write(1, "\n", 1);
	g_status = 128 + signum;
	_exit(g_status);
}

/**
 * @brief
 * Function to handle the signals.
 * To be called inside prompt, with heredoc and inside the childs,
 * it takes the caller as argument to know what to do.
 * @param int (PROMPT, EXEC, HEREDOC)
*/
void	set_signals(int caller)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	if (caller == PROMPT)
	{
		signal(SIGINT, SIG_DFL);
		sa.sa_handler = handle_ctrlc;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (caller == EXEC)
	{
		signal(SIGINT, SIG_IGN);
		sa.sa_handler = handle_ctrlc_exec;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = handle_ctrld_exec;
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (caller == HEREDOC)
	{
		sa.sa_handler = handle_ctrlc_heredoc;
		sigaction(SIGINT, &sa, NULL);
	}
}
