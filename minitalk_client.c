/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:14:33 by seohyeki          #+#    #+#             */
/*   Updated: 2024/02/26 13:14:56 by seohyeki         ###   ########.fr       */
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
	while (argv[2][i])
	{
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	send_signal(server_pid, '\0');
	return (0);
}
