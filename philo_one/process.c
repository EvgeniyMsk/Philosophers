/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:32:49 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 14:32:50 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	eating(t_philo *p)
{
	if (!p->t_last_meal)
	{
		if (pthread_mutex_unlock(p->lock_last_meal))
			print_error(MUTEX);
		return (END);
	}
	if (gettimeofday(p->t_last_meal, NULL))
		print_error(TIME);
	if (print(p->param->t_start, p->t_last_meal, p->n, " is eating\n"))
		print_error(MALLOC);
	p->n_eat++;
	usleep(p->param->t_eat * 1000);
	if (pthread_mutex_unlock(p->lock_last_meal))
		print_error(MUTEX);
	return (SUCCESS);
}

static int	check_eating(t_philo *p)
{
	int				ret;
	struct timeval	t_action;
	size_t			time;

	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	if (pthread_mutex_lock(p->lock_last_meal))
		print_error(MUTEX);
	time = (size_t)((t_action.tv_sec - p->t_last_meal->tv_sec) * 1000
				+ (t_action.tv_usec - p->t_last_meal->tv_usec) * 0.001);
	if (!p->t_last_meal || time > p->param->t_die)
	{
		free(p->t_last_meal);
		p->t_last_meal = NULL;
		if (print(p->param->t_start, &t_action, p->n, " is died\n"))
			print_error(MALLOC);
	}
	ret = eating(p);
	if (pthread_mutex_unlock(p->r_fork->fork))
		print_error(MUTEX);
	if (pthread_mutex_unlock(p->l_fork->fork))
		print_error(MUTEX);
	return (ret);
}

static int	routine(t_philo *p)
{
	struct timeval	t_action;

	if (check_eating(p) || p->n_eat == p->param->n_must_eat)
		return (END);
	if (gettimeofday(&t_action, NULL))
		return (TIME);
	if (print(p->param->t_start, &t_action, p->n, " is sleeping\n"))
		print_error(MALLOC);
	usleep(p->param->t_sleep * 1000);
	if (!p->t_last_meal)
		return (END);
	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	if (print(p->param->t_start, &t_action, p->n, " is thinking\n"))
		print_error(MALLOC);
	return (SUCCESS);
}

static int	taking_forks(t_philo *p)
{
	int				i;
	t_fork			*fork;
	struct timeval	t_action;

	i = 0;
	if (!p->t_last_meal)
		return (END);
	fork = ((p->n + i) % 2) ? p->l_fork : p->r_fork;
	while (i < 2)
	{
		if (fork->n_last != p->n)
		{
			if (pthread_mutex_lock(fork->fork))
				print_error(MUTEX);
			if (gettimeofday(&t_action, NULL))
				print_error(TIME);
			if (print(p->param->t_start, &t_action, p->n, " has taken fork\n"))
				print_error(MALLOC);
			if ((fork->n_last = p->n) && ++i != 2)
				fork = ((p->n + i) % 2) ? p->l_fork : p->r_fork;
		}
	}
	return (SUCCESS);
}

void		*ft_do_processing(void *as)
{
	t_philo *p;

	p = (t_philo *)as;
	while (!taking_forks(p) && !routine(p))
		;
	return (NULL);
}
