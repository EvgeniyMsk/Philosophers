/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:31 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 15:08:43 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	wait_philo(t_task_3 *p)
{
	int		n_end;
	int		status;
	t_philo	*ptr;

	status = 0;
	n_end = 0;
	ptr = p->philo;
	while (!status && p->param->n_philo > n_end)
	{
		if (waitpid(-1, &status, 0) < 0)
			print_error(FORK);
		n_end++;
	}
	if (status)
	{
		ptr = p->philo;
		while (ptr)
		{
			kill(ptr->pid, SIGINT);
			ptr = ptr->next;
		}
	}
	return (SUCCESS);
}

int			run_philo(t_task_3 *p)
{
	int		pid;
	t_philo	*ptr;

	if (!(p->param->t_start = malloc(sizeof(struct timeval))))
		return (MALLOC);
	if (gettimeofday(p->param->t_start, NULL))
		return (TIME);
	ptr = p->philo;
	while (ptr)
	{
		ptr->t_last_meal->tv_sec = p->param->t_start->tv_sec;
		ptr->t_last_meal->tv_usec = p->param->t_start->tv_usec;
		ptr->n_eat = 0;
		if (!(ptr->param = ft_param_dup(p->param)))
			return (MALLOC);
		if (!(pid = fork()))
			ft_do_processing(ptr);
		if ((ptr->pid = pid) < 0)
			return (FORK);
		ptr = ptr->next;
	}
	wait_philo(p);
	usleep(100000);
	return (SUCCESS);
}
