/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:53:25 by wvan-der          #+#    #+#             */
/*   Updated: 2023/11/16 17:05:04 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

char	*ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*ft_strjoin(char *str, char c)
{
	int		len;
	char	*temp;
	int		i;

	len = 0;
	i = 0;
	while (str && str[len])
		len++;
	temp = malloc(len + 2);
	if (!temp)
		return (ft_free(&str), NULL);
	while (str && str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = c;
	temp[++i] = 0;
	ft_free(&str);
	str = temp;
	return (str);
}

void	bin_to_char(int signum, int *c)
{
	if (signum == SIGUSR1)
	{
		*c = (*c << 1) | 1;
	}
	else if (signum == SIGUSR2)
	{
		*c = *c << 1;
	}
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid;
	static int	i;
	static int	c;
	static char	*str;

	(void)context;
	pid = info->si_pid;
	bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			ft_printf("%s", str);
			ft_free(&str);
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		str = ft_strjoin(str, c);
		if (!str)
			exit(1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &sig_handler;
	ft_printf("PID: %d\n", getpid());
	if (sigaction(SIGUSR1, &sa, 0) == -1)
	{
		ft_printf("error");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, 0) == -1)
	{
		ft_printf("error");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
