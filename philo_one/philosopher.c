/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:11:49 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 14:36:53 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		ft_set_philosophers(t_task_1 *p)
{
	t_philo	*tmp;
	t_philo	*ptr;
	t_philo	*odd;
	t_philo	*even;

	ptr = p->philo;
	odd = p->philo;
	tmp = p->philo->next;
	even = p->philo->next;
	while (ptr)
	{
		if ((ptr->n % 2) && ptr->n != 1)
		{
			odd->next = ptr;
			odd = odd->next;
		}
		else if (!(ptr->n % 2) && ptr->n != 2)
		{
			even->next = ptr;
			even = even->next;
		}
		ptr = ptr->next;
	}
	odd->next = tmp;
	even->next = NULL;
}

static int	wait_philo(t_task_1 *p)
{
	int		c;
	t_philo	*ptr;

	ptr = p->philo;
	while (ptr && !usleep(1000) &&
			(c = ptr->n_eat < p->param->n_must_eat ? 0 : c + 1) > -2)
		if (!ptr->t_last_meal || !ptr->next)
			ptr = (ptr->t_last_meal && c < p->param->n_philo) ? p->philo : NULL;
		else
			ptr = ptr->next;
	c = 0;
	ptr = p->philo;
	while (c < p->param->n_philo)
	{
		if (pthread_mutex_lock(ptr->lock_last_meal))
			return (MUTEX);
		c += !ptr->t_last_meal ? 1 : !!(ptr->t_last_meal = NULL) + 0;
		if (pthread_mutex_unlock(ptr->lock_last_meal))
			return (MUTEX);
		if (!(ptr = ptr->next) && c != p->param->n_philo)
			ptr = !(c *= 0) ? p->philo : NULL;
	}
	return (SUCCESS);
}

int			run_philo(t_task_1 *p)
{
	t_philo	*ptr;

	if (!(p->param->t_start = malloc(sizeof(struct timeval))))
		return (MALLOC);
	gettimeofday(p->param->t_start, NULL);
	ptr = p->philo;
	while (ptr)
	{
		ptr->l_fork->n_last = 0;
		ptr->r_fork->n_last = 0;
		if (!(ptr->t_last_meal = malloc(sizeof(struct timeval))))
			return (MALLOC);
		ptr->t_last_meal->tv_sec = p->param->t_start->tv_sec;
		ptr->t_last_meal->tv_usec = p->param->t_start->tv_usec;
		ptr->n_eat = 0;
		ptr->param = ft_param_dup(p->param);
		if (!(ptr->lock_last_meal = malloc(sizeof(pthread_mutex_t))))
			return (MALLOC);
		if (pthread_mutex_init(ptr->lock_last_meal, NULL))
			return (MUTEX);
		if ((pthread_create(ptr->thread, NULL, &ft_do_processing, ptr)))
			return (PTHREAD);
		ptr = ptr->next;
	}
	return ((wait_philo(p) ? MUTEX : SUCCESS) + usleep(100000));
}
