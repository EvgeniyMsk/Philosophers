/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:11:36 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/03 14:51:10 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		ft_initialize_ph_2(t_task_1 *p, t_philo **ptr, \
			t_fork **r_fork, int i)
{
	if (!((*ptr)->thread = malloc(sizeof(pthread_t))))
		return (MALLOC);
	if (i == p->param->n_philo)
		(*ptr)->r_fork = p->philo->l_fork;
	else if (!((*ptr)->r_fork = malloc(sizeof(t_fork))))
		return (MALLOC);
	*r_fork = (*ptr)->r_fork;
	if ((i != p->param->n_philo) &&
		!((*ptr)->r_fork->fork = malloc(sizeof(pthread_mutex_t))))
		return (MALLOC);
	if (pthread_mutex_init((*r_fork)->fork, NULL))
		return (MUTEX);
	if (i != p->param->n_philo && !((*ptr)->next = malloc(sizeof(t_philo))))
		return (MALLOC);
	else if (i == p->param->n_philo)
		(*ptr)->next = NULL;
	return (SUCCESS);
}

int				ft_initialize_ph(t_task_1 *p)
{
	int			ret;
	int			i;
	t_philo		*ptr;
	t_fork		*r_fork;

	i = 0;
	if (!(p->philo = malloc(sizeof(t_philo)))
						|| !(r_fork = malloc(sizeof(t_fork)))
						|| !(r_fork->fork = malloc(sizeof(pthread_mutex_t))))
		return (MALLOC);
	if (pthread_mutex_init(r_fork->fork, NULL))
		return (MUTEX);
	ptr = p->philo;
	while (ptr && p->param->n_philo > i++)
	{
		ptr->n = i;
		ptr->l_fork = r_fork;
		if ((ret = ft_initialize_ph_2(p, &ptr, &r_fork, i)))
			return (ret);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int				init(int ac, char **av, t_task_1 *p)
{
	if (!(p->param = malloc(sizeof(t_param))))
		return (MALLOC);
	p->param->t_start = NULL;
	if (ft_atoi(av[1], (size_t *)&p->param->n_philo))
		return (WRONG_ARG);
	if (p->param->n_philo < 2)
		return (ONE_FORK);
	if (ft_atoi(av[2], &p->param->t_die))
		return (WRONG_ARG);
	if (ft_atoi(av[3], &p->param->t_eat))
		return (WRONG_ARG);
	if (ft_atoi(av[4], &p->param->t_sleep))
		return (WRONG_ARG);
	if (ac == 5)
		p->param->n_must_eat = -1;
	else if (ac == 6 && ft_atoi(av[5], &p->param->n_must_eat))
		return (WRONG_ARG);
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	int			ret;
	t_task_1	p;

	if (ac < 5 || ac > 6)
		return (print_error(WRONG_ARG));
	p.philo = NULL;
	if ((ret = init(ac, av, &p)))
		return (print_error(ret) + ft_clean(&p));
	if (!p.param->n_must_eat)
		return (ft_clean(&p));
	if ((ret = ft_initialize_ph(&p)))
		return (print_error(ret) + ft_clean(&p));
	ft_set_philosophers(&p);
	if ((ret = run_philo(&p)))
		return (print_error(ret) + ft_clean(&p));
	ft_clean(&p);
	return (SUCCESS);
}
