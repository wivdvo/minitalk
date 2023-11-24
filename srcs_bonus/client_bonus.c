/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:53:18 by wvan-der          #+#    #+#             */
/*   Updated: 2023/11/10 17:25:11 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static int	g_flag;

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;

	(void)info;
	(void)context;
	g_flag = 1;
	if (signum == SIGUSR2)
		i++;
	else if (signum == SIGUSR1)
	{
		i = i / 8;
		ft_printf("Message received. (%dbytes)\n", i);
	}
}

void	char_to_bin(char c, int pid)
{
	int	wait_for_response;
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		wait_for_response = 0;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_flag == 0)
		{
			if (wait_for_response == 5)
			{
				ft_printf("No response from server");
				exit(0);
			}
			wait_for_response++;
			sleep(1);
		}
		g_flag = 0;
		bit_index--;
	}
}

int	init_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &sig_handler;
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		return (ft_printf("error"), 0);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (ft_printf("error"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*str;
	int					i;

	if (init_sigaction() == 0)
		exit(1);
	if (argc != 3)
		ft_printf("Wrong number of arguments");
	else
	{
		pid = ft_atoi(argv[1]);
		if (pid < 0)
			return (ft_printf("Invalid PID!"), 1);
		str = argv[2];
		i = 0;
		while (str && str[i])
			char_to_bin(str[i++], pid);
		char_to_bin(0, pid);
	}
	return (0);
}
