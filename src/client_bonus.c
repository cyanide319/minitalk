/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:11:17 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/08/11 21:55:37 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	minus;

	nb = 0;
	minus = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '+')
			str++;
		else if (*str == '-')
		{
			minus *= -1;
			str++;
		}
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - 48;
		str++;
	}
	return (nb * minus);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	sig_receiver(int signum, siginfo_t *info, void *context)
{
	static int	c_received;

	(void)*info;
	(void)*context;
	if (signum == SIGUSR1)
		c_received++;
	else
	{
		ft_printf ("character received: %d", c_received);
		exit(0);
	}
}

void	sig_sender(int pid, char *str)
{
	int			i;
	char		c;

	while (*str)
	{
		i = 0;
		c = *str;
		while (i < 8)
		{
			if (c & 128)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			c <<= 1;
			i++;
		}
		str++;
	}
	i = 8;
	while (i-- > 0)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Error. Need two arguments; pid + message. \n");
		return (1);
	}
	ft_printf("Character sent: %d \n", ft_strlen(argv[2]));
	sa.sa_sigaction = &sig_receiver;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sig_sender(ft_atoi(argv[1]), argv[2]);
	return (0);
}
