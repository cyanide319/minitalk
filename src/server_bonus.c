/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:49:59 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/08/11 22:15:42 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

typedef struct s_server{
	unsigned char	c;
	int				bits;
}	t_server;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static t_server		server;
	static pid_t		client_pid = 0;

	server.c += (signum == SIGUSR2);
	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (++server.bits == 8)
	{
		server.bits = 0;
		if (server.c == '\0')
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			ft_printf("\n");
			return ;
		}
		write (1, &server.c, 1);
		server.c = 0;
		kill(client_pid, SIGUSR1);
	}	
	else
		server.c <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &sig_handler;
	sa.sa_flags = SA_RESTART;
	ft_printf("PID: %d \n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause ();
	return (0);
}
