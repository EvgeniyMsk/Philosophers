/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:48 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 15:08:50 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		rec_msg(char *msg, char **ptr)
{
	while (*msg)
		*(*ptr)++ = *msg++;
}

static void		rec_nbr(size_t nbr, char **ptr)
{
	char			c;
	size_t			nbr_tmp;
	long long		pow;

	pow = 10;
	nbr_tmp = nbr;
	while (nbr_tmp /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + 48;
		*(*ptr)++ = c;
	}
}

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int				print_error(int error)
{
	if (error == WRONG_ARG)
		write(2, "Error: wrong arguments\n",
		ft_strlen("Error: wrong arguments\n"));
	else if (error == MALLOC)
		write(2, "Error: malloc error\n",
		ft_strlen("Error: malloc error\n"));
	else if (error == SEMAPHORE)
		write(2, "Error: semaphore error\n",
		ft_strlen("Error: semaphore error\n"));
	else if (error == FORK)
		write(2, "Error: fork error\n",
		ft_strlen("Error: fork error\n"));
	else if (error == SLEEP)
		write(2, "Error: usleep error\n",
		ft_strlen("Error: usleep error\n"));
	else if (error == TIME)
		write(2, "Error: gettimeofday error\n",
		ft_strlen("Error: gettimeofday error\n"));
	else if (error == ONE_FORK)
		write(2, "Error: philosopher can't eat with one fork\n",
		ft_strlen("Error: philosopher can't eat with one fork\n"));
	return (error);
}

int				print(struct timeval *st, struct timeval *tv,
									size_t number, char *msg)
{
	char		*ptr;
	char		*log;
	size_t		size_n;
	long long	tmp;
	long long	time;

	tmp = number * 10;
	size_n = 4 + ft_strlen(msg);
	while (tmp /= 10)
		size_n++;
	time = (tv->tv_sec - st->tv_sec) * 1000 +
		(tv->tv_usec - st->tv_usec) * 0.001;
	tmp = time;
	while (tmp /= 10)
		size_n++;
	if (!(log = malloc(sizeof(char) * (size_n))))
		return (MALLOC);
	ptr = log;
	rec_nbr((size_t)time, &ptr);
	rec_msg("ms ", &ptr);
	rec_nbr(number, &ptr);
	rec_msg(msg, &ptr);
	write(1, log, size_n);
	free(log);
	return (SUCCESS);
}
