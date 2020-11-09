/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:43:06 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 15:43:07 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	wait_philo(t_task_2 *p)
{
	int		c;
	t_philo	*ptr;

	c = 0;
	ptr = p->philo;
	while (ptr && !usleep(1000) &&
				(c = (ptr->n_eat < p->param->n_must_eat) ? 0 : c + 1) > -2)
		if (!ptr->t_last_meal || !ptr->next)
			ptr = (ptr->t_last_meal && c < p->param->n_philo) ? p->philo : NULL;
		else
			ptr = ptr->next;
	c = 0;
	ptr = p->philo;
	while (c < p->param->n_philo)
	{
		if (sem_wait(ptr->sem_last_meal))
			return (SEMAPHORE);
		c += (!ptr->t_last_meal) ? 1 : !!(ptr->t_last_meal = NULL) + 0;
		if (sem_post(ptr->sem_last_meal))
			return (SEMAPHORE);
		if (!(ptr = ptr->next) && c != p->param->n_philo)
			ptr = !(c *= 0) ? p->philo : ptr;
	}
	return (SUCCESS);
}

int			run_philo(t_task_2 *p)
{
	t_philo	*ptr;

	if (!(p->param->t_start = malloc(sizeof(struct timeval))))
		return (MALLOC);
	gettimeofday(p->param->t_start, NULL);
	ptr = p->philo;
	while (ptr && !(ptr->n_eat = 0))
	{
		ptr->t_last_meal->tv_sec = p->param->t_start->tv_sec;
		ptr->t_last_meal->tv_usec = p->param->t_start->tv_usec;
		if (!(ptr->param = ft_param_dup(p->param)))
			return (MALLOC);
		ptr = ptr->next;
	}
	ptr = p->philo;
	while (ptr)
	{
		if (pthread_create(ptr->thread, NULL, &ft_do_processing, ptr))
			return (PTHREAD);
		ptr = ptr->next;
	}
	if (wait_philo(p))
		return (SEMAPHORE);
	usleep(100000);
	return (SUCCESS);
}
