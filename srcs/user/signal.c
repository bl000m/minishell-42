/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:51:32 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/01 22:10:35 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	signal(SIGINT, SIG_IGN);
	if (caller == OFF)
		return ;
	if (caller == PROMPT)
	{
		sa.sa_flags |= SA_SIGINFO;
		signal(SIGINT, SIG_DFL);
		sa.sa_sigaction = handle_signal_prompt;
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (caller == EXEC)
	{
		signal(SIGINT, SIG_IGN);
		sa.sa_handler = handle_signal_exec;
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (caller == HEREDOC)
		sa.sa_handler = handle_ctrlc_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_signal_prompt(int sign, siginfo_t *info, void *context)
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
	}
	if (sign == SIGQUIT)
		printf("\b\b  \b\b");
	if (!info->si_pid)
		exit(128 + sign);
	g_status = 128 + sign;
}

void	handle_signal_exec(int sign)
{
	if (sign == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
	if (sign == SIGINT)
		write(1, "\n", 1);
	g_status = 128 + sign;
}

void	handle_ctrlc_heredoc(int sign)
{
	write(1, "\n", 1);
	g_status = 128 + sign;
	close(STDIN_FILENO);
}
