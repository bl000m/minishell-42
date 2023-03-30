/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:51:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/28 20:33:07 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrlc_exec(int sign);

void	handle_ctrlc(int sign, siginfo_t *info, void *context)
{
	static int	pid = 0;

	if (!pid)
		pid = info->si_pid;
	(void) context;
	if (sign == SIGINT)
	{
		if (info->si_pid == pid)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		// else
			// handle_ctrlc_exec(sign);
	}
	if (sign == SIGQUIT)
		printf("\b\b  \b\b");
	g_status = 128 + sign;
}

void	handle_ctrld_exec(int sign)
{
	printf("Quit (core dumped)\n");
	g_status = 128 + sign;
	exit(g_status);
}

void	handle_ctrlc_exec(int sign)
{
	write(1, "\n", 1);
	g_status = 128 + sign;
	signal(SIGINT, SIG_IGN);
	// exit(g_status);
}

void	handle_ctrlc_heredoc(int sign)
{
	write(1, "\n", 1);
	g_status = 128 + sign;
	// printf("g_status = %d\n", g_status);
	close(STDIN_FILENO);
	// exit(g_status);
}

/**
 * @brief
 * Function to handle the signals.
 * To be called inside prompt, with heredoc and inside the childs,
 * it takes the caller as argument to know what to do.
 * @param int (PROMPT, EXEC, HEREDOC or OFF)
*/
void	set_signals(int caller)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	if (caller == PROMPT)
	{
		sa.sa_flags |= SA_SIGINFO;
		signal(SIGINT, SIG_DFL);
		sa.sa_sigaction = handle_ctrlc;
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
	if (caller == OFF)
		signal(SIGINT, SIG_IGN);
}
