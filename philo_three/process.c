/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:54 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 15:08:55 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	eating(t_philo *p)
{
	if (!p->t_last_meal)
		return (END);
	if (gettimeofday(p->t_last_meal, NULL))
		print_error(TIME);
	print(p->param->t_start, p->t_last_meal, p->n, " is eating\n");
	p->n_eat++;
	usleep(p->param->t_eat * 1000);
	return (SUCCESS);
}

static int	check_eating(t_philo *p)
{
	int				ret;
	struct timeval	t_action;
	size_t			time;

	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	time = (size_t)((t_action.tv_sec - p->t_last_meal->tv_sec) * 1000
				+ (t_action.tv_usec - p->t_last_meal->tv_usec) * 0.001);
	if (!p->t_last_meal || time > p->param->t_die)
	{
		free(p->t_last_meal);
		print(p->param->t_start, &t_action, p->n, " died\n");
		p->t_last_meal = NULL;
		ret = -1;
	}
	else
		ret = eating(p);
	if (sem_post(p->param->forks))
		print_error(SEMAPHORE);
	if (sem_post(p->param->forks))
		print_error(SEMAPHORE);
	if (sem_post(p->param->a_eat))
		print_error(SEMAPHORE);
	return (ret);
}

static int	routine(t_philo *p)
{
	struct timeval	t_action;

	if (check_eating(p))
		return (DIED);
	if (p->n_eat == p->param->n_must_eat)
		return (END);
	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	print(p->param->t_start, &t_action, p->n, " is sleeping\n");
	usleep(p->param->t_sleep * 1000);
	if (!p->t_last_meal)
		return (END);
	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	print(p->param->t_start, &t_action, p->n, " is thinking\n");
	return (SUCCESS);
}

static int	taking_forks(t_philo *p)
{
	struct timeval	t_action;

	if (!p->t_last_meal)
		return (END);
	if (sem_wait(p->param->a_eat))
		print_error(SEMAPHORE);
	if (sem_wait(p->param->forks))
		print_error(SEMAPHORE);
	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	print(p->param->t_start, &t_action, p->n, " has taken a fork\n");
	if (sem_wait(p->param->forks))
		print_error(SEMAPHORE);
	if (gettimeofday(&t_action, NULL))
		print_error(TIME);
	print(p->param->t_start, &t_action, p->n, " has taken a fork\n");
	return (SUCCESS);
}

void		ft_do_processing(t_philo *p)
{
	int	ret;

	while (!taking_forks(p) && !(ret = routine(p)))
		;
	if (ret == DIED)
		exit(1);
	exit(0);
}
