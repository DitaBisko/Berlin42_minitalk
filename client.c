/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:43:18 by dbisko            #+#    #+#             */
/*   Updated: 2024/08/06 14:56:33 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	flag;

	result = 0;
	sign = 1;
	flag = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (flag == 0)
		{
			if (*str == '-')
				sign = -sign;
			flag = 1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	send_message(char *msg, int pid)
{
	int		i;
	int		sig;
	char	c;

	while (1)
	{
		c = *msg;
		i = 0;
		while (i < 8)
		{
			sig = (*msg >> (7 - i)) & 1;
			if (sig == 0)
				kill(pid, SIGUSR1);
			else if (sig == 1)
				kill(pid, SIGUSR2);
			i++;
			usleep(60);
		}
		msg++;
		if (c == '\0')
			break ;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (kill(pid, 0) == -1)
		{
			write(2, "Invalid PID or permission denied\n", 33);
			return (1);
		}
		send_message(av[2], pid);
		return (0);
	}
	else
	{
		write(2, "Usage: ./client PID \"Message\"\n", 30);
		write(2, "Escape special characters using \\\n", 34);
		return (1);
	}
}
