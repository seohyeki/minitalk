/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:49:53 by seohyeki          #+#    #+#             */
/*   Updated: 2024/02/26 13:25:34 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_sigdata	g_data;

static void	get_signal(int sig, siginfo_t *info, void *s)
{
	(void)s;
	if (sig == SIGUSR2)
		g_data.c += (1 << g_data.count);
	(g_data.count)++;
	if (g_data.count == 8)
	{
		write(1, &g_data.c, 1);
		if (g_data.c == '\0')
			kill(info->si_pid, SIGUSR1);
		g_data.count = 0;
		g_data.c = 0;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	g_data.count = 0;
	g_data.c = 0;
	(void)argv;
	if (argc == 1)
	{
		ft_printf("server_pid: %d\n", getpid());
		sigemptyset(&act.sa_mask);
		sigaddset(&act.sa_mask, SIGUSR1);
		sigaddset(&act.sa_mask, SIGUSR2);
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = &get_signal;
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		while (1)
			pause();
	}
	return (0);
}
