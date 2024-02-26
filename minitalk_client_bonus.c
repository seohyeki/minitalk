/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:14:33 by seohyeki          #+#    #+#             */
/*   Updated: 2024/02/26 13:29:17 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_signal(pid_t pid, char c)
{
	int	n;

	n = 0;
	while (n < 8)
	{
		if ((c & (1 << n)) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		n++;
		usleep(100);
	}
}

static void	handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "success!\n", 9);
	exit(0);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	size_t	i;

	server_pid = ft_atoi(argv[1]);
	i = 0;
	if (argc != 3)
	{
		ft_printf("error\n");
		return (0);
	}
	signal(SIGUSR1, &handler);
	while (argv[2][i])
	{
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	send_signal(server_pid, '\0');
	while (1)
		pause();
	return (0);
}
