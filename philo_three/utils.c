/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:59 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 15:09:01 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	cpy->forks = param->forks;
	cpy->a_eat = param->a_eat;
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
	return (0);
}

static void	clean_philo(t_philo *p)
{
	if (p->param)
		free(p->param->t_start);
	free(p->param);
	free(p->t_last_meal);
	free(p);
}

int			ft_clean(t_task_3 *p)
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
	{
		if (p->param->forks && sem_close(p->param->forks))
			print_error(SEMAPHORE);
		if (p->param->a_eat && sem_close(p->param->a_eat))
			print_error(SEMAPHORE);
		free(p->param->t_start);
	}
	if (p)
		free(p->param);
	return (SUCCESS);
}
