/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:43:34 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/09 13:00:02 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	put_pid(int pid)
{
	char	digit;

	if (pid >= 10)
		put_pid(pid / 10);
	digit = pid % 10 + '0';
	write(1, &digit, 1);
}

void	handle_signal(int sig)
{
	static int				bit_count;
	static unsigned char	c;

	if (sig == SIGUSR1)
		c = (c << 1) | 0;
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	//sigaction(SIGUSR1, &sa, NULL);
	//sigaction(SIGUSR2, &sa, NULL);
	pid = (getpid());
	write(1, "Server PID:", 11);
	put_pid(pid);
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
