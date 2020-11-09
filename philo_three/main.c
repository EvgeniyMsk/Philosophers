/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:10 by qsymond           #+#    #+#             */
/*   Updated: 2020/11/09 09:13:08 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				ft_initialize_ph(t_task_3 *p)
{
	int			i;
	t_philo		*ptr;

	if (!(p->philo = malloc(sizeof(t_philo))))
		return (MALLOC);
	i = 0;
	ptr = p->philo;
	while (ptr && p->param->n_philo > i++)
	{
		ptr->n = i;
		if (!(ptr->t_last_meal = malloc(sizeof(struct timeval))))
			return (MALLOC);
		if (i < p->param->n_philo && !(ptr->next = malloc(sizeof(t_philo))))
			return (MALLOC);
		else if (i == p->param->n_philo)
			ptr->next = NULL;
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int				init(int ac, char **av, t_task_3 *p)
{
	if (!(p->param = malloc(sizeof(t_param))))
		return (MALLOC);
	if (ft_atoi(av[1], (size_t *)&p->param->n_philo))
		return (WRONG_ARG);
	if (p->param->n_philo < 2)
		return (ONE_FORK);
	sem_unlink("/forks");
	if (!(p->param->forks = sem_open("/forks",
		O_CREAT, S_IRWXU, p->param->n_philo)))
		return (SEMAPHORE);
	sem_unlink("/a_eat");
	if (!(p->param->a_eat = sem_open("/a_eat",
		O_CREAT, S_IRWXU, (int)(p->param->n_philo / 2))))
		return (SEMAPHORE);
	if (ft_atoi(av[2], &p->param->t_die) ||
		ft_atoi(av[3], &p->param->t_eat) || ft_atoi(av[4], &p->param->t_sleep))
		return (WRONG_ARG);
	if (ac == 5)
		p->param->n_must_eat = -1;
	else if (ac == 6 && ft_atoi(av[5], (size_t *)&p->param->n_must_eat))
		return (WRONG_ARG);
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	int			ret;
	t_task_3	p;

	if (ac < 5 || ac > 6)
		return (print_error(WRONG_ARG));
	p.philo = NULL;
	if ((ret = init(ac, av, &p)))
		return (print_error(ret) + ft_clean(&p));
	if (!p.param->n_must_eat)
		return (ft_clean(&p));
	if ((ret = ft_initialize_ph(&p)))
		return (print_error(ret) + ft_clean(&p));
	if ((ret = run_philo(&p)))
		return (print_error(ret) + ft_clean(&p));
	ft_clean(&p);
	return (SUCCESS);
}
