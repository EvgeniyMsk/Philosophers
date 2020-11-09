/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:32:32 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 14:32:34 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_param		*ft_param_dup(t_param *param)
{
	t_param	*cpy;

	if (!(cpy = malloc(sizeof(t_param))))
		return (NULL);
	cpy->n_philo = param->n_philo;
	cpy->t_die = param->t_die;
	cpy->t_eat = param->t_eat;
	cpy->t_sleep = param->t_sleep;
	cpy->n_must_eat = param->n_must_eat;
	if (!(cpy->t_start = malloc(sizeof(struct timeval))))
	{
		free(cpy);
		return (NULL);
	}
	cpy->t_start->tv_sec = param->t_start->tv_sec;
	cpy->t_start->tv_usec = param->t_start->tv_usec;
	return (cpy);
}

int			ft_atoi(char *str, size_t *nbr)
{
	if (*str == '\0')
		return (DIED);
	*nbr = 0;
	while (*str >= '0' && *str <= '9')
		*nbr = *nbr * 10 + (*str++ - 48);
	if (*str != '\0')
		return (DIED);
	return (SUCCESS);
}

static void	clean_philo(t_philo *p)
{
	if (p->param)
		free(p->param->t_start);
	free(p->param);
	if (p->l_fork && p->l_fork->fork && pthread_mutex_destroy(p->l_fork->fork))
		print_error(MUTEX);
	if (p->l_fork)
		free(p->l_fork->fork);
	free(p->l_fork);
	if (p->lock_last_meal && pthread_mutex_destroy(p->lock_last_meal))
		print_error(MUTEX);
	free(p->lock_last_meal);
	free(p->thread);
	free(p->t_last_meal);
	free(p);
}

int			ft_clean(t_task_1 *p)
{
	void			*tmp;
	t_philo			*ptr;

	ptr = (p) ? p->philo : NULL;
	while (ptr)
	{
		tmp = ptr->next;
		clean_philo(ptr);
		ptr = tmp;
	}
	if (p && p->param)
		free(p->param->t_start);
	if (p)
		free(p->param);
	return (SUCCESS);
}
